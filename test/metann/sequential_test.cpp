//
// Created by 10580.
//
#include <iostream>
#include <concepts>
#include "metann/facilities/sequential.hpp"

using namespace metann;

template<typename ...Ts>
struct type_list;

void match_void_ptr(void *ptr)
{
    std::cout << *(int*)ptr << std::endl;

}

void test_create_at()
{
    using namespace sequential;
    using type = create_t<type_list, int, 3>;
    static_assert(std::is_same_v<type, type_list<int, int, int>>);

    using t1 = type_list<char, int, long, double>;
    static_assert(std::same_as<long, at_t<t1, 2>>);

    int a = 5;
    int *pa = &a;
    match_void_ptr(pa);
    void *pv = pa;
    std::cout << "create at passed!" << std::endl;

}

void test_order()
{
    using namespace sequential;
    using t1 = type_list<char, int, long, double>;
    static_assert(order_v<t1, char> == 0);
    static_assert(order_v<t1, int> == 1);
    static_assert(order_v<t1, long> == 2);
    static_assert(order_v<t1, double> == 3);
    std::cout << "order passed!" << std::endl;

}

struct A;
struct B;
struct C;
struct D;
struct E;
struct F;
struct G;
struct H;
struct M;
struct X;
struct Y;
struct node;




void test_set()
{
    using namespace sequential;
    using t1 = type_list<char, int, long, long long, float, double, A, B, C, D, E, F,G, H, M, X,Y>;
    using t2 = set_t<t1, 16, node>;
    using t3 = type_list<char,int, long, long long, float, double, A, B, C, D, E, F,G, H, M, X,node>;
    using t6 = type_list<char,int, long, long long, float, double, A, B, node, D, E, F,G, H, M, X,node>;
    static_assert(std::same_as<t2, t3>);
    static_assert(std::same_as<set_t<t3, 8, node>, t6>);
    using t4 = type_list<char>;
    using t5 = set_t<t4, 0, int>;
    static_assert(std::same_as<t5, type_list<int>>);
    std::cout << "set passed!" << std::endl;

}

template<typename T0, typename T1>
struct add
{
    static constexpr auto value = T0::value + T1::value;

};

void test_fold()
{
    using namespace sequential;
    using namespace utility;
    using t1 = type_list<int_<1>,int_<2>,int_<3>,int_<4>,
            int_<5>,int_<6>,int_<7>,int_<8>,int_<9>,int_<10>>;

    constexpr auto r = fold_t<int_<0>, t1, add>::value;
    static_assert(r == 55);
    std::cout << "fold passed!" << std::endl;

}

template<typename T>
struct trans_f;

template<template<int> typename T, int I>
struct trans_f<T<I>>
{
    using type = T<2*I>;
};



void test_transform()
{
    using namespace utility;
    using t1 = type_list<int_<1>,int_<2>,int_<3>,int_<4>,
            int_<5>,int_<6>,int_<7>,int_<8>,int_<9>,int_<10>>;
    using r = sequential::transform_t<t1, trans_f, type_list>;
    static_assert(std::same_as<r, type_list<int_<2>,int_<4>,int_<6>,int_<8>,
            int_<10>,int_<12>,int_<14>,int_<16>,int_<18>,int_<20>>>);
    std::cout << "transform passed!" << std::endl;
}

void test_cascade()
{
    using namespace sequential;
    using t1 = type_list<char, unsigned , int>;
    using t2 = type_list<long, float, double>;
    using t3 = cascade_t<t1, t2>;
    static_assert(std::same_as<t3, type_list<char, unsigned, int, long, float, double>>);
    std::cout << "cascade passed!" << std::endl;
}

void test_push_back()
{
    using namespace sequential;
    using t1 = type_list<char, unsigned , int>;
    using t2 = push_back_t<t1, long, float, double>;
    static_assert(std::same_as<t2, type_list<char, unsigned, int, long, float, double>>);
    std::cout << "push_back passed!" << std::endl;
}

void test_size_head_tail()
{
    using namespace sequential;
    using t1 = type_list<char,unsigned ,int, long, float, double>;
    static_assert(size_v<t1> == 6);
    static_assert(std::same_as<head_t<t1>, char>);
    static_assert(std::same_as<tail_t<t1>, type_list<unsigned,int,long,float,double>>);

    std::cout << "size head tail passed!" << std::endl;
}



int main(int argc, char *argv[])
{
    test_size_head_tail();
    test_push_back();
    test_cascade();
    test_create_at();
    test_order();
    test_set();
    test_fold();
    test_transform();
    return 0;
}