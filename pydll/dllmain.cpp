// dllmain.cpp : Defines the entry point for the DLL application.
#define BOOST_PYTHON_STATIC_LIB

#include "stdafx.h"
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
using namespace boost::python;

#include <memory>



BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
    )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

class Player

{

public:
    enum MyEnum
    {
        TS0,
        TS1,
        TS2
    };

    Player(int height, int age) :

        _height(height), _age(age) {}

    void SetHeight(int hei)
    {
        _height = hei;
    }

    int GetHeight() const
    {
        return _height;
    }

    void SetAge(int age)
    {
        _age = age;
    }

    int GetAge() const
    {
        return _age;
    }


    void SetItem(list& item) {        

        auto n = len(item);
        std::shared_ptr<char> n_char = std::make_shared<char>(int(n));

        for (auto i = 0; i < n; ++i)
        {
            unsigned char it = extract<unsigned char>(item[i]);
            //printf("%x", it);
            item[i] = 0x55;
        }
        //printf("\n");
    }

private:
    int _height;
    int _age;
};

class A
{
public:
    A() { privateVal = 0; }                      //默认构造函数
    A(int val) { privateVal = val; }             //带参数的构造函数
    void set(int val) { privateVal = val; }      //成员函数
    int get() const { return privateVal; };   //成员函数
    int publicVal;                          //公共数据成员
private:
    int privateVal;                         //私有数据成员
};

int addA(A &a, int addVal)
{
    int val = a.get();
    val += addVal;
    a.set(val);
    return val;
}


BOOST_PYTHON_MODULE(pydll)
{
    enum_<Player::MyEnum>("MyEnum")
        .value("TS0", Player::TS0)
        .value("TS1", Player::TS1)
        .value("TS2", Player::TS2)
        ;
    class_<Player>("Player", init<int, int>())
        .def("SetHeight", &Player::SetHeight)
        .def("GetHeight", &Player::GetHeight)
        .def("SetAge", &Player::SetAge)
        .def("GetAge", &Player::GetAge)
        .def("SetItem", &Player::SetItem)
        ;

    def("addA", &addA);
}
