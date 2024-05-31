#pragma once
#include <functional>

template <typename ReturnType, typename... Args>
class Delegate
{
public:
    Delegate();
    ~Delegate() = default;

    template <typename T>
    void Bind(T* obj, ReturnType (T::*method)(Args...));
    void Bind(std::function<ReturnType(Args...)> lambda);
    void Unbind();

    bool IsBound() const;

    ReturnType Execute(Args... args);

private:
    std::function<ReturnType(Args...)> function_;
};

template <typename ReturnType, typename... Args>
Delegate<ReturnType, Args...>::Delegate() :
    function_(nullptr)
{
}

template <typename ReturnType, typename... Args>
template <typename T>
void Delegate<ReturnType, Args...>::Bind(T* obj, ReturnType (T::*method)(Args...))
{
    function_ = [obj, method](Args... args) -> ReturnType
    {
        return (obj->*method)(std::forward<Args>(args)...);
    };
}

template <typename ReturnType, typename... Args>
void Delegate<ReturnType, Args...>::Bind(std::function<ReturnType(Args...)> lambda)
{
    function_ = std::move(lambda);
}

template <typename ReturnType, typename... Args>
void Delegate<ReturnType, Args...>::Unbind()
{
    function_ = nullptr;
}

template <typename ReturnType, typename... Args>
bool Delegate<ReturnType, Args...>::IsBound() const
{
    return function_ != nullptr;
}

template <typename ReturnType, typename... Args>
ReturnType Delegate<ReturnType, Args...>::Execute(Args... args)
{
    return function_(std::forward<Args>(args)...);
}
