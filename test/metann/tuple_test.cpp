//
// Created by 10580.
//
#include "metann/facilities/tuple.hpp"

using namespace metann;

void tuple()
{

    using t1 = tuple_cat_t<std::tuple<int>, std::tuple<char>, std::tuple<float>>;
    static_assert(std::same_as<t1, std::tuple<int, char, float>>);
    info(tuple_cat);

    using t2 = tuple_at_t<std::tuple<char,int,float, long,double>, 0>;
    using t3 = tuple_at_t<std::tuple<char,int,float, long,double>, 1>;
    using t4 = tuple_at_t<std::tuple<char,int,float, long,double>, 2,3,4>;
    static_assert(std::same_as<std::tuple<char>, t2>);
    static_assert(std::same_as<std::tuple<int>, t3>);
    static_assert(std::same_as<std::tuple<float,long,double>, t4>);
    info(tuple_at);

    using t5 = tuple_remove_t<std::tuple<char,int,float,long,double>, float>;
    static_assert(std::same_as<t5, std::tuple<char,int,long,double>>);


}









int main(int argc, char *argv[])
{
    tuple();



    return 0;
}



