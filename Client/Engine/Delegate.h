#pragma once
#include <functional>

template <typename Type>
class Delegate
{
public:
    Delegate();
    ~Delegate() = default;
    
    template <typename T, typename ... Args>
    void Add(T* obj, Type(T::* method)(Args...), Args... args);

    Type Execute()
    {
        return function_();
    }

private:
    std::function<Type()> function_;
    
};

template <typename T>
Delegate<T>::Delegate()
{
}

template <typename Type>
template <typename T, typename ... Args>
void Delegate<Type>::Add(T* obj, Type(T::* method)(Args...), Args... args)
{
    function_ = std::bind(method, obj, args...);
}
