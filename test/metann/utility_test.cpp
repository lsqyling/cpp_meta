//
// Created by 10580.
//
#include <iostream>
#include "metann/facilities/utility.hpp"

using namespace metann::utility;

template<int ...Is>
constexpr void print_index_sequence(index_sequence<Is...>)
{
    ((std::cout << Is << ' '),  ...);
    std::cout << std::endl;
}




void test_make_index_sequence()
{
    print_index_sequence(make_index_sequence_t<100>{});
}





int main(int argc, char *argv[])
{
    test_make_index_sequence();




    return 0;
}






