#pragma once
#include <functional>

template <typename Type, typename ... Args>
class Delegate
{
public:
    Delegate();
    ~Delegate() = default;
    
    template <typename T>
    void AddDynamic(T* obj, Type(T::* method)(Args...));

    void AddLambda(std::function<Type(Args...)> lambda);

    Type Execute(Args... args)
    {
        return function_(std::forward<Args>(args)...);
    }

private:
    std::function<Type(Args...)> function_;
    
};

template <typename Type, typename ... Args>
Delegate<Type, Args...>::Delegate()
{
}

template <typename Type, typename ... Args>
template <typename T>
void Delegate<Type, Args...>::AddDynamic(T* obj, Type(T::* method)(Args...))
{
    function_ = [obj, method](Args... args) -> Type
    {
        return (obj->*method)(std::forward<Args>(args)...);
    };
}

template <typename Type, typename ... Args>
void Delegate<Type, Args...>::AddLambda(std::function<Type(Args...)> lambda)
{
    function_ = std::move(lambda);
}
