#pragma once

#include <iostream>
#include <functional>

template<typename T>
class Reflection {
public:
    T* typePointer;

    Reflection(T* obj) {
        typePointer = obj;
        Reflect();
    }

    T* Reflect() {
        std::cout << typeid(*typePointer).name() << "\n";
        return typePointer;
    }

    //// 멤버 함수 포인터 타입 정의
    //using FunctionPtr = std::function<void(T&, const std::vector<std::string>&)>;


    // 클래스의 멤버 함수를 매핑
    //std::map<std::string, FunctionPtr> functionMap;
    //// 멤버 함수를 매핑
    //template<typename Func>
    //void mapFunction(const std::string& name, Func func) {
    //    functionMap[name] = [=](T& obj, const std::vector<std::string>& args) {
    //        func(obj, args);
    //    };
    //}

    // //멤버 함수 실행
    //template<typename T>
    //void callFunction(T& obj, const std::string& name, const std::vector<std::string>& args) {
    //    auto it = functionMap.find(name);
    //    if (it != functionMap.end()) {
    //        it->second(obj, args);
    //    }
    //    else {
    //        std::cout << "Function '" << name << "' not found!" << std::endl;
    //    }
    //}
};
