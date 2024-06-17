#pragma once
#include <memory>
#include <type_traits>
#include <tuple>

template<typename>
class Delegate;

template<typename>
class Function;

template<typename Ret, typename... Args>
class Function<Ret(Args...)>
{
public:
    Function() = delete;
    virtual ~Function() = default;

    template<typename F, typename = typename std::enable_if<!std::is_same<Function, typename std::decay<F>::type>::value>::type>
    Function(F&& func)
        : func_(std::make_shared<LCallable<typename std::decay<F>::type>>(std::forward<F>(func))), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t>(const_cast<std::decay_t<F>*>(&func));
    }

    Function(Ret(*func)(Args...))
        : func_(std::make_shared<GCallable>(func)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t>(func);
    }

    Function(Ret(*func)(Args...), Args... args)
        : func_(std::make_shared<FCallable>(func, args...)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t>(func);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, Ret(M::*func)(Args...))
        : func_(std::make_shared<MCallable<M>>(target, func)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, Ret(M::* func)(Args...), Args... args)
        : func_(std::make_shared<CCMCallable<M>>(target, func, std::forward<Args>(args)...)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, Ret(M::*func)(Args...) const)
        : kFunc_(std::make_shared<CMCallable<M>>(target, func))
    {
        std::memcpy(&addr_, &func, sizeof(&addr_));
        //addr_ = reinterpret_cast<uintptr_t>(&func);
    }

    Ret operator()(Args&&... args) const
    {
        if (kFunc_)
            return (*kFunc_)(std::forward<Args>(args)...);
        return (*func_)(std::forward<Args>(args)...);
    }

    Ret operator()() const
    {
        if (kFunc_)
            return (*kFunc_)();
        return (*func_)();
    }

    void operator=(const Function& input)
    {
        this->addr_ = input.addr_;
        this->func_ = input.func_;
    }

    std::uintptr_t GetAddr() const { return addr_; }

private:
    using Func = Ret(*)(Args...);
    template<typename U>
    using MFunc = Ret(U::*)(Args...);

    struct ICallable
    {
        virtual ~ICallable() = default;
        virtual Ret operator()(Args&&... args) const 
        {
            return Ret();
        };

        virtual Ret operator()() const abstract;
        
    };

    struct GCallable : public ICallable
    {
        GCallable(Ret(*func)(Args...)) : func_(func) {}
        virtual Ret operator()(Args&&... args) const override
        {
            return func_(std::forward<Args>(args)...);
        }
        Ret(*func_)(Args...);
    };

    template<typename F>
    struct LCallable : public ICallable
    {
        LCallable(F&& func) : func_(std::move(func)) {};
        virtual Ret operator()(Args&&... args) const override
        {
            return func_(std::forward<Args>(args)...);
        }
        virtual Ret operator()() const override
        {
            return Ret();
        }


        F func_;
    };

    template<typename M>
    struct MCallable : public ICallable
    {
        MCallable(M* target, Ret(M::* func)(Args...)) : func_(func), target_(target) {}
        virtual Ret operator()(Args&&... args) const override
        {
            return (target_->*func_)(std::forward<Args>(args)...);
        }
        
        M* target_;
        Ret(M::* func_)(Args...);
    };

    template<typename M>
    struct CMCallable : public ICallable
    {
        CMCallable(M* target, Ret(M::* func)(Args...) const)
            : target_(target), func_(func) {}
        virtual Ret operator()(Args&&... args) const override
        {
            return (target_->*func_)(std::forward<Args>(args)...);
        }
        
        M* target_;
        Ret(M::* func_)(Args...) const;
    };

    template<typename M>
    struct CCMCallable : public ICallable
    {
        CCMCallable(M* target, Ret(M::* func)(Args...), Args... args)
            : target_(target), func_(func), args_(std::make_tuple(args...)) {}
        virtual Ret operator()(Args&&... args) const override
        {
            return (target_->*func_)(std::forward<Args>(args)...);
        }

        virtual Ret operator()() const override
        {
            return std::apply([this](auto&&... args)->Ret 
                {
                    return (target_->*func_)(std::forward<decltype(args)>(args)...);
                }
                ,args_);
        }

        M* target_;
        Ret(M::* func_)(Args...);
        std::tuple<Args...> args_;
    };

    struct FCallable : public ICallable
    {
        FCallable(Ret(*func)(Args...), Args... args) 
            : args_(std::make_tuple(args...)), func_(func)
        {};
        virtual Ret operator()(Args&&... args) const override
        {
            return std::apply(func_, args_);
        }

        Ret operator()() override
        {
            return std::apply(func_, args_);
        }

        std::tuple<Args...> args_;
        Ret(*func_)(Args...);
    };

private:
    std::shared_ptr<ICallable> func_;
    const std::shared_ptr<ICallable> kFunc_;
    std::uintptr_t addr_;
    
    template<typename>
    friend class Delegate;
};

template<>
class Function<void(void)>
{
public:
    Function() = delete;
    virtual ~Function() = default;

    template<typename L, typename = typename std::enable_if<!std::is_same<Function, typename std::decay<L>::type>::value>::type, typename... Args>
    Function(L&& func)
        : func_(std::make_shared<LCallable<typename std::decay<L>::type>>(std::forward<L>(func))), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t>(const_cast<std::decay_t<L>*>(&func));
    }

    template<typename M>
    Function(M* target, void(M::* func)())
        : func_(std::make_shared<MCallable<M>>(target, func)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    }

    template<typename M>
    Function(M* target, void(M::* func)() const)
        : kFunc_(std::make_shared<CMCallable<M>>(target, func))
    {
        std::memcpy(&addr_, &func, sizeof(&addr_));
    }

    Function(void(*func)(void))
        : func_(std::make_shared<GCallable>(func)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    };

    template<typename... Args>
    Function(void(*func)(Args...), const Args&&... kArgs)
        : func_(std::make_shared<GGCallable>(func, std::forward<Args>(kArgs)...)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    };

    Function(void(*func)(const std::wstring&), const std::wstring& kStr)
        : func_(std::make_shared<SCallable>(func, kStr)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, void(M::*func)(const std::wstring&), const std::wstring& kStr)
        : func_(std::make_shared<SCallable>(target, func, kStr)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    }

    template<typename... Args>
    Function(void(*func)(Args...), Args... args)
        : func_(std::make_shared<AGCallable<Args...>>(func, args...)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    };

    template<typename M, typename... Args>
    Function(M* target, void(M::*func)(Args...), Args... args) //typename std::enable_if<std::is_class<M>::value>::type
        : func_(std::make_shared<AMCallable<M, Args...>>(target, func, args...)), kFunc_(nullptr)
    {
        addr_ = reinterpret_cast<std::uintptr_t&>(func);
    };

    void operator()() const
    {
        if (kFunc_)
            return (*kFunc_)();
        return (*func_)();
    }

    void operator=(const Function& input)
    {
        this->addr_ = input.addr_;
        this->func_ = input.func_;
    }

    std::uintptr_t GetAddr() const { return addr_; }

private:
    struct ICallable
    {
        virtual ~ICallable() = default;
        virtual void operator()() const = 0;
    };

    struct GCallable : public ICallable
    {
        GCallable(void(*func)(void)) 
            : func_(func)
        {};
        virtual void operator()(void) const override
        {
            (*func_)();
        }
        void(*func_)(void);
    };

    template<typename... Args>
    struct GGCallable : public ICallable
    {
        GGCallable(void(*func)(Args...), const Args&&... kArgs)
            : args_(std::make_tuple(std::forward<Args>(kArgs)...)), func_(func)
        {};

        virtual void operator()() const override
        {
            std::apply(func_, args_);
        }

        void(*func_)(Args...);
        std::tuple<Args...> args_;
    };

    struct SCallable : public ICallable
    {
        SCallable(void(*func)(const std::wstring&), const std::wstring& kStr)
            : str_(kStr), func_(func)
        {};

        virtual void operator()() const override
        {
            (*func_)(str_);
        }

        void(*func_)(const std::wstring&);
        const std::wstring& str_;
    };

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    struct SMCallable : public ICallable
    {
        SMCallable(M* target, void(M::*func)(const std::wstring&), const std::wstring& kStr)
            : target_(target), str_(kStr), func_(func)
        {};

        virtual void operator()() const override
        {
            (*func_)(str_);
        }
        M* target_;
        void(M::*func_)(const std::wstring&);
        const std::wstring& str_;
    };

    template<typename... Args>
    struct AGCallable : public ICallable
    {
        AGCallable(void(*func)(Args...), Args... args)
            : func_(func), args_(std::make_tuple(args...))
        {};
        virtual void operator()(void) const override
        {
            std::apply(func_, args_);
        }
        void(*func_)(Args...);
        std::tuple<Args...> args_;
    };

    template<typename M>
    struct MCallable : public ICallable
    {
        MCallable(M* target, void(M::* func)()) : func_(func), target_(target) {}
        virtual void operator()() const override
        {
            (target_->*func_)();
        }

        M* target_;
        void(M::* func_)();
    };

    template<typename M, typename... Args>
    struct AMCallable : public ICallable
    {
        AMCallable(M* target, void(M::* func)(Args...), Args... args)
            : func_(func), target_(target), args_(std::make_tuple(args...))
        {};
        virtual void operator()() const override
        {
            std::apply([this](auto&&... args)
                {
                    (target_->*func_)(std::forward<decltype(args)>(args)...);
                }, args_);
        }

        M* target_;
        void(M::*func_)(Args...);
        std::tuple<Args...> args_;
    };

    template<typename M>
    struct CMCallable : public ICallable
    {
        CMCallable(M* target, void(M::* func)() const)
            : target_(target), func_(func) {}
        virtual void operator()() const override
        {
            (target_->*func_)();
        }

        M* target_;
        void(M::* func_)() const;
    };

    template<typename L, typename... Args>
    struct LCallable : public ICallable
    {
        LCallable(L&& func, Args&&... args)
            : func_(std::forward<L>(func)), args_(std::make_tuple(std::forward<Args>(args)...))
        {};
        virtual void operator()() const override
        {
            std::apply([&](auto&&... args) {
                func_(std::forward<decltype(args)>(args)...);
                }, args_);
        }

        L func_;
        std::tuple<Args...> args_;
    };

private:
    std::shared_ptr<ICallable> func_;
    const std::shared_ptr<ICallable> kFunc_;
    std::uintptr_t addr_;

    template<typename>
    friend class Delegate;
};
