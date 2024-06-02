#pragma once
#include <memory>
#include <type_traits>
#include <any>

template<typename>
class Delegate;

template<typename>
class Function;

template<typename Ret, typename... Args>
class Function<Ret(Args...)>
{
public:
    Function() = delete;

    template<typename F, typename = typename std::enable_if<!std::is_same<Function, typename std::decay<F>::type>::value>::type>
    Function(F&& func)
        : func_(std::make_shared<LCallable<typename std::decay<F>::type>>(std::forward<F>(func))), cFunc_(nullptr)
    {
        addr_ = reinterpret_cast<uintptr_t>(const_cast<std::decay_t<F>*>(&func));
    }

    Function(Ret(*func)(Args...))
        : func_(std::make_shared<GCallable>(func)), cFunc_(nullptr)
    {
        addr_ = reinterpret_cast<uintptr_t>(func);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, Ret(M::* func)(Args...))
        : func_(std::make_shared<MCallable<M>>(target, func)), cFunc_(nullptr)
    {
        addr_ = reinterpret_cast<uintptr_t>(std::decay_t<M*>(&func));
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    Function(M* target, Ret(M::*func)(Args...) const)
        : cFunc_(std::make_shared<CMCallable<M>>(target, func))
    {
        std::memcpy(&addr_, &func, sizeof(&addr_));
        //addr_ = reinterpret_cast<uintptr_t>(&func);
    }

    Ret operator()(Args&&... args) const
    {
        if (cFunc_)
            return (*cFunc_)(std::forward<Args>(args)...);
        return (*func_)(std::forward<Args>(args)...);
    }

    Function operator=(const Function& input)
    {
        return input;
    }

    std::uintptr_t& GetAddr() { return addr_; }

    std::any GetFunc() { return func_.get()->GetFunc(); }

private:
    using Func = Ret(*)(Args...);
    template<typename U>
    using MFunc = Ret(U::*)(Args...);



    struct ICallable
    {
        virtual ~ICallable() {}
        virtual Ret operator()(Args&&... args) const = 0;
        virtual std::any GetFunc() const = 0;
    };

    struct GCallable : public ICallable
    {
        GCallable(Ret(*func)(Args...)) : func_(func) {}
        virtual Ret operator()(Args&&... args) const override
        {
            return func_(std::forward<Args>(args)...);
        }
        //Func GetFunc() { return func_; }
        virtual std::any GetFunc() const override { return func_; }
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
        //F GetFunc() { return func_; }
        virtual std::any GetFunc() const override { return func_; }
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
        //MFunc<M> GetFunc() { return func_; }
        virtual std::any GetFunc() const override { return func_; }

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
        //MFunc<M> GetFunc() { return func_; }
        virtual std::any GetFunc() const override { return func_; }

        M* target_;
        Ret(M::* func_)(Args...) const;
    };

private:
    std::shared_ptr<ICallable> func_;
    const std::shared_ptr<ICallable> cFunc_;
    std::uintptr_t addr_;
    
    template<typename>
    friend class Delegate;
};