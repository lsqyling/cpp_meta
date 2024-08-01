//
// Created by 10580.
//
#include <utility>
#include <iostream>
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
    using type = create_t<type_list, int, 3>;
    static_assert(std::is_same_v<type, type_list<int, int, int>>);

    using t1 = type_list<char, int, long, double>;
    static_assert(std::same_as<long, at_t<t1, 2>>);

    int a = 5;
    int *pa = &a;
    match_void_ptr(pa);
    void *pv = pa;
}



int main(int argc, char *argv[])
{
    test_create_at();
    return 0;
}