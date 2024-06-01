#pragma once
#include <functional>
#include <vector>
using namespace std;

template<typename Ret, typename... Args>
class MDelegate
{
	using Func = Ret(*)(Args...);
	template<typename T>
	using MFunc = Ret(T::*)(Args...);
	using Functor = std::function<Ret(Args...)>;

public:
	void Bind(Func&& func)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &func, sizeof(func));
		addrs_.push_back(tt);


		Functor func_ = func;
		functions_.push_back(std::move(func_));
	}

	template<typename T>
	void Bind(Ret(T::*method)(Args...), T* target)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &method, sizeof(method));
		addrs_.push_back(tt);

		Functor func_ = [target, method](Args&&... args) ->Ret
			{
				return (target->*method)(std::forward<Args>(args)...);
			};
		functions_.push_back(std::move(func_));
	}

	void Execute(Args... args)
	{
		for (auto& temp : functions_)
		{
			temp(args...);
		}
	}

	void UnBind(Func&& func)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &func, sizeof(func));

		auto fnit = functions_.begin();
		for (auto it = addrs_.begin(); it != addrs_.end(); ++it)
		{
			if (*it == tt)
			{
				addrs_.erase(it);
				functions_.erase(fnit);
				break;
			}
			++fnit;
		}
	}

	template<typename T>
	void UnBind(MFunc<T>&& func)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &func, sizeof(func));
		auto fnit = functions_.begin();
		for (auto it = addrs_.begin(); it != addrs_.end(); ++it)
		{
			if (*it == tt)
			{
				addrs_.erase(it);
				functions_.erase(fnit);
				break;
			}
			++fnit;
		}
	}


	const bool& IsBound(Func&& func)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &func, sizeof(func));

		for (const auto& temp : addrs_)
		{
			if (tt == temp)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	const bool& IsBound(MFunc<T>&& func)
	{
		std::uintptr_t tt = 0;
		std::memcpy(&tt, &func, sizeof(func));

		for (const auto& temp : addrs_)
		{
			if (tt == temp)
			{
				return true;
			}
		}
		return false;
	}

	vector<Functor> functions_;
	vector<uintptr_t> addrs_;


};