#pragma once
#include <functional>

template <typename Type, typename... Args>
class Delegate
{
public:
    Delegate();
    ~Delegate() = default;

    template <typename T>
    void Bind(T* obj, Type (T::*method)(Args...));
    void Bind(std::function<Type(Args...)> lambda);
    void Unbind();

    bool IsBound() const;

    Type Execute(Args... args);

private:
    std::function<Type(Args...)> function_;
};

template <typename Type, typename... Args>
Delegate<Type, Args...>::Delegate() :
    function_(nullptr)
{
}

template <typename Type, typename... Args>
template <typename T>
void Delegate<Type, Args...>::Bind(T* obj, Type (T::*method)(Args...))
{
    function_ = [obj, method](Args... args) -> Type
    {
        return (obj->*method)(std::forward<Args>(args)...);
    };
}

template <typename Type, typename... Args>
void Delegate<Type, Args...>::Bind(std::function<Type(Args...)> lambda)
{
    function_ = std::move(lambda);
}

template <typename Type, typename... Args>
void Delegate<Type, Args...>::Unbind()
{
    function_ = nullptr;
}

template <typename Type, typename... Args>
bool Delegate<Type, Args...>::IsBound() const
{
    return function_ != nullptr;
}

template <typename Type, typename... Args>
Type Delegate<Type, Args...>::Execute(Args... args)
{
    return function_(std::forward<Args>(args)...);
}
