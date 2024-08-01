//
// Created by 10580.
//
#include <iostream>
#include "catch_amalgamated.hpp"
#include "meta/types.hpp"



struct A
{
//private:
    int a{};
    int b{};

    void say_a() const { std::cout << "say_a(): a = " << a << std::endl; }

};

struct B : private A
{
    void say()
    {
        std::cout << this->a << std::endl;
        this->say_a();
    }
    using A::say_a;
};

struct C : private A
{
     C(A) {}
};

template<typename CC>
constexpr auto func(CC c)
{
    std::cout << "func" << std::endl;
}



TEST_CASE("derived-private")
{
    SECTION("test1")
    {
        B b;
        b.say();
        b.say_a();
    }

    SECTION("test2")
    {
        const A a;
        C c(a);

        func(c);
    }
}




TEST_CASE("type_list-constexpr-testing")
{
    using namespace meta;

    SECTION("head()")
    {
        type_list_<int, long, char> tl;
        auto head = tl.head();
        STATIC_REQUIRE(std::is_same_v<decltype(head), int>);
        auto tail = tl.tail();
        STATIC_REQUIRE(std::is_same_v<decltype(tail), type_list_<long, char>>);
        STATIC_REQUIRE(tail.size() == 2);
        auto first = std::get<0>(std::make_tuple(0, 0LL, '0'));
        STATIC_REQUIRE(std::is_same_v<decltype(first), int>);

    }

    SECTION("type_const-dispatch")
    {
        const type_const<char> tl;
        const type_const<char> &t2 = tl;
        STATIC_REQUIRE(std::is_same_v<get_type<type_const<char>{}>, char>);
        STATIC_REQUIRE(std::is_same_v<get_type<tl>, char>);

        STATIC_REQUIRE(dispatch_value<3>{} == 3);
        STATIC_REQUIRE(dispatch_value<value_const<3>{}>{} == 3);
        STATIC_REQUIRE(std::same_as<dispatch_value<value_const<3>{}>, value_const<3>>);
        STATIC_REQUIRE(std::same_as<dispatch_value<type_list_<char,int>{}>, type_list_<char,int>>);
    }

    SECTION("make_index_sequence")
    {
        constexpr auto seq = std::make_index_sequence<10>{};
        STATIC_REQUIRE(seq.size() == 10);

    }













}


