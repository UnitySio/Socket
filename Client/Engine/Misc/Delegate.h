#pragma once
#include "Function.h"
#include <vector>

template<typename>
class Delegate;

template<typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
public:
    Delegate() {}

    template<typename F, typename = typename std::enable_if<!std::is_same<Function<Ret(Args...)>, typename std::decay<F>::type>::value>::type>
    void Bind(F&& func)
    {
        auto temp = std::make_shared<Function<Ret(Args...)>>(std::forward<F>(func));
        functions_.push_back(*temp);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    void Bind(M* target, Ret(M::* func)(Args...))
    {
        auto temp = std::make_shared<Function<Ret(Args...)>>(target, func);
        functions_.push_back(*temp);
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    void Bind(M* target, Ret(M::* func)(Args...) const)
    {
        auto temp = std::make_shared<Function<Ret(Args...)>>(target, func);
        functions_.push_back(*temp);
    }

    void Bind(Ret(*func)(Args...))
    {
        auto temp = std::make_shared<Function<Ret(Args...)>>(func);
        functions_.push_back(*temp);
    }

    void Execute(Args&&...args) const
    {
        for (const auto& temp : functions_)
        {
            temp(std::forward<Args>(args)...);
        }
    }

    template<typename F, typename = typename std::enable_if<!std::is_same<Function<Ret(Args...)>, typename std::decay<F>::type>::value>::type>
    void UnBind(F func)
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                functions_.erase(it);
                break;
            }
            ++it;
        }
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    void UnBind(Ret(M::* func)(Args...))
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                functions_.erase(it);
                break;
            }
            ++it;
        }
    }

    void UnBind(Ret(*func)(Args...))
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                functions_.erase(it);
                break;
            }
            ++it;
        }
    }

    template<typename F, typename = typename std::enable_if<!std::is_same<Function<Ret(Args...)>, typename std::decay<F>::type>::value>::type>
    const bool& IsBound(F func)
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                functions_.erase(it);
                return true;
            }
        }
        return false;
    }

    template<typename M, typename std::enable_if<std::is_class<M>::value>::type* = nullptr>
    const bool& IsBound(Ret(M::* func)(Args...))
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                functions_.erase(it);
                return true;
            }
        }
        return false;
    }

    const bool& IsBound(Ret(*func)(Args...))
    {
        std::uintptr_t tt = 0;
        std::memcpy(&tt, &func, sizeof(func));
        auto it = functions_.begin();
        for (auto& temp : functions_)
        {
            if (temp.GetAddr() == tt)
            {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<Function<Ret(Args...)>> functions_;
};
