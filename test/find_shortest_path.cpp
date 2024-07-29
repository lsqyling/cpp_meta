//
// Created by 10580.
//

#include <iostream>
#include "meta/template/shortest_path.hpp"
#include "catch_amalgamated.hpp"


template<char Id>
struct node_
{
    static constexpr char id = Id;
};

using A = node_<'A'>;
using B = node_<'B'>;
using C = node_<'C'>;
using D = node_<'D'>;
using E = node_<'E'>;

using g = meta::graph<
        link(node(A)->node(B)->node(C)->node(D)),
        link(node(A)->node(C)),
        link(node(B)->node(A)),
        link(node(A)->node(E))>;


TEST_CASE("shortest-path-testing")
{
    SECTION("find_path")
    {
        STATIC_REQUIRE(g::get_path('A', 'D').sz == 3);
        STATIC_REQUIRE(g::get_path('A', 'A').sz == 1);
        STATIC_REQUIRE(g::get_path('B', 'D').sz == 3);
        STATIC_REQUIRE(g::get_path('B', 'E').sz == 3);
    }

    SECTION("runtime")
    {
        char from = 'A';
        char to = 'D';
        auto path = g::get_path(from, to);
        std::cout << std::format("from '{}' to '{}', path size: {}\n", from, to, path.sz);
        for (int i = 0; i < path.sz; ++i)
        {
            std::cout << path.path[i];
            if (i != path.sz - 1)
                std::cout << "->";
        }
        std::cout << std::endl;
    }





}





