#pragma once
#include <iostream>
#include <typeinfo>
// 게임 내 모든 요소를 상속받는 클래스.
template<typename T>
class Object {
public:
	virtual void GetType(T *obj) {
		// 해당 오브젝트의 타입을 가져옴.
		//std::cout << typeid(obj).name()<< "\n";
		return;
	}
};