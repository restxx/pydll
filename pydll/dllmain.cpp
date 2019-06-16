// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <memory>
#include <iostream>

#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
using namespace boost::python;

typedef unsigned char   UCHAR;

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


    void SetItem(list& item) 
    {        
        auto n = len(item);
        //std::unique_ptr<UCHAR []> char_Ptr(new UCHAR [int(n)]() ); //初始值用0填充
        auto char_Ptr = std::make_unique<UCHAR []>(n);  //初始值用默认0填充
        auto array = char_Ptr.get();
    
        for (auto i = 0; i < n; ++i)
        {   
            UCHAR it = extract<UCHAR>(item[i]);
            array[i] = it;

            printf("%x ", array[i]);
            item[i] = 0x55;
        }
        printf("\n");
        std::cout << char_Ptr.get() << std::endl;
    }

    void SetDict(dict &dc)
    {
        //int it = extract<int>(dc.attr('test'));
        //printf("%d\n", extract<int>(dc.get('test')));
    }

    void SetUint(UINT a) 
    {
        printf("%u\n", a);
        printf("%d\n", a);
        printf("%x\n", a);
        printf("%X\n", a);
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



class EncDec
{
public:
    EncDec(){}
    ~EncDec(){}

    int Dec(list &items, int start, int End,  bool enc) 
    {
        auto nlen = (End == 0 ? len(items) - start : End - start);

        auto char_Ptr = std::make_unique<UCHAR[]>(nlen);  //初始值用默认0填充
        auto array = char_Ptr.get();
        for (auto i = 0; i < nlen; ++i)
        {
            UCHAR it = extract<UCHAR>(items[start + i]);
            array[i] = it;
        }
        //假装解密 替换8的倍数长度
        auto n = nlen - nlen % 8;
        memset(array, 1, n);

        //回写到list
        for (auto i = 0; i < nlen; ++i)
        {
            items[start + i] = array[i];
        }

        return nlen % 8;
    }
};


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
        .def("SetDict", &Player::SetDict)
        .def("SetUint", &Player::SetUint)
        ;
    
    def("addA", &addA);

    class_<EncDec>("EncDec")
        .def("Dec", &EncDec::Dec)

        ;
}

//auto func = PyInit_pydll;