//
// Created by 10580.
//
#include "metann/facilities/type_list.hpp"



using namespace metann;

template<typename ...T>
struct predicate
{
    static constexpr bool value = ((sizeof(T) == 4) && ...);
};

using list = type_list<char, int, long, float, double>;
using empty = type_list<>;

void test_aux()
{
    static_assert(is_less<3, 4>);
    static_assert(negate<predicate>::type<char, int, long, float, double>::value);
    static_assert(is_not_same<char, int>::value);
    info(is_less);
    info(negate);
    info(is_not_same);
}

template<typename ...Ts>
struct cont;

void test_type_list()
{
    static_assert(std::same_as<type_list_from_t<cont<char, int, float>>, type_list<char, int, float>>);
    static_assert(std::same_as<type_list_from_t<cont<>>, type_list<>>);
    info(type_list_from);

    using t0 = type_list<char, int>;
    using t1 = t0::append<long, float, double>;
    using t2 = t0::prepend<long, float, double>;
    static_assert(std::same_as<t1, type_list<char,int,long,float,double>>);
    static_assert(std::same_as<t2, type_list<long,float, double,char,int>>);
    info(append);
    info(prepend);
    using t3 = t0::to<predicate>;
    static_assert(std::same_as<t3, predicate<char, int>>);
    info(to);

    static_assert(std::same_as<head_t<t0>, char>);
    static_assert(std::same_as<tail_t<t0>, type_list<int>>);
    static_assert(std::same_as<last_t<t0>, int>);
    info(head);
    info(tail);
    info(last);
}
























int main(int argc, char *argv[])
{
    test_type_list();
    test_aux();





    return 0;
}


















