//
// Created by 10580.
//

#include <iostream>
#include "catch_amalgamated.hpp"
#include "meta/template/type_list.hpp"


namespace fold_expr {
template<int ...i>
constexpr int ladd_sum = (0 + ... + i);
template<int ...i>
constexpr int radd_sum = (i + ... + 0);

// (((((0-1)-2)-3)-4)-5)...
template<int ...i>
constexpr int lsub_sum = (0 - ... - i);
// ...(1-(2-(3-(4-(5-0)))))
template<int ...i>
constexpr int rsub_sum = (i - ... - 0);
}

namespace detail {
template<typename ...Ts> struct list;
struct node {};

template<typename T>
using size_less4 = std::bool_constant<sizeof(T) < 4>;

template<typename Acc, typename E>
using size_type_sum = std::integral_constant<size_t, Acc::value + sizeof(E)>;

using Acc = std::integral_constant<size_t, 0>;

template<typename L, typename R>
using cmp = std::bool_constant<sizeof(L) < sizeof(R)>;


}

TEST_CASE("type_list-alg")
{
    using namespace meta;
    SECTION("concat")
    {
        using tl0 = type_list<char, int>;
        using tl1 = type_list<float, double>;
        using tl2 = type_list<long, long long>;
        STATIC_REQUIRE(std::is_same_v<concat_t<tl0, tl1, tl2>,
                type_list<char, int, float, double, long, long long>>);
        std::cout << "concat passed!" << std::endl;
    }
    SECTION("elem")
    {
        using typelist = type_list<char, int, float, double, long, long long, detail::node>;
        STATIC_REQUIRE(elem_v<typelist, detail::node>);
        STATIC_REQUIRE(!elem_v<typelist, char*>);
        std::cout << "elem passed!" << std::endl;

    }
    SECTION("unique")
    {
        using typelist = type_list<char, int, float, double, char, long, detail::node, long, long long, detail::node>;
        STATIC_REQUIRE(std::is_same_v<unique_t<typelist>,
                type_list<char,int,float,double,long,detail::node,long long>>);
        std::cout << "unique passed!" << std::endl;
    }

    SECTION("partition")
    {
        using typelist = type_list<char, int, float, double, char, long, detail::node, long, long long, detail::node>;
        using splitbysize4 = meta::partition_t<typelist, detail::size_less4>;

        STATIC_REQUIRE(std::is_same_v<splitbysize4::satisfied,
                type_list<char,char,detail::node,detail::node>>);
        STATIC_REQUIRE(std::is_same_v<splitbysize4::rest,
                type_list<int,float,double,long,long,long long>>);

        std::cout << "partition passed!" << std::endl;
    }
    SECTION("sort")
    {
        using typelist = type_list<char, int, float, double, char, long>;


        STATIC_REQUIRE(std::is_same_v<sort_t<typelist, detail::cmp>,
                type_list<char,char,int,float, long, double>>);

        std::cout << "sort passed!" << std::endl;
    }

    SECTION("flatten")
    {
        using typelist = type_list<char, type_list<int, type_list<int, double>>,
                type_list<double, char, long>, unsigned>;

        STATIC_REQUIRE(std::is_same_v<flatten_t<typelist>,
                type_list<char,int,int,double,double, char, long, unsigned>>);

        std::cout << "flatten passed!" << std::endl;
    }
}



TEST_CASE("type_list-testing")
{
    SECTION("type_list")
    {
        using typelist = meta::type_list<char, int>;
        STATIC_REQUIRE(meta::TypeList<typelist>);
        STATIC_REQUIRE(std::is_same_v<typelist::append<long, float, detail::node>,
                        meta::type_list<char, int, long, float, detail::node>>);
        STATIC_REQUIRE(std::is_same_v<typelist::preappend<long, float, detail::node>,
                        meta::type_list<long, float, detail::node, char, int>>);
        STATIC_REQUIRE(std::is_same_v<typelist::to<meta::type_list>,
                meta::type_list<char, int>>);

        STATIC_REQUIRE(std::is_same_v<typelist::to<detail::list>,
                detail::list<char, int>>);
        std::cout << "type_list passed!" << std::endl;
    }
    SECTION("map")
    {
        using typelist = meta::type_list<char, float, double, int, char, detail::node>;
        STATIC_REQUIRE(std::is_same_v<meta::map_t<typelist, std::add_pointer>,
                meta::type_list<char*, float*, double *, int *, char *, detail::node *>>);
        std::cout << "map passed!" << std::endl;
    }

    SECTION("filter")
    {
        using typelist = meta::type_list<char, float, double, int, long long,
                unsigned long long, char, detail::node>;

        STATIC_REQUIRE(std::is_same_v<meta::filter_t<typelist, detail::size_less4>,
                meta::type_list<char, char, detail::node>>);
        std::cout << "filter passed!" << std::endl;
    }

    SECTION("fold")
    {
        using typelist = meta::type_list<char, float, double, int, long long,
                unsigned long long, char, detail::node>;

        STATIC_REQUIRE(meta::fold_t<typelist, detail::Acc, detail::size_type_sum>::value
                               == 35);
        std::cout << "fold passed!" << std::endl;
    }
}


TEST_CASE("fold_expr-testing")
{
    SECTION("fold_expr")
    {
        using namespace fold_expr;
        std::cout << std::format("ladd_sum<1...10> = {}\n", ladd_sum<1, 2, 3, 4, 5, 6>);
        std::cout << std::format("radd_sum<1...10> = {}\n", radd_sum<1, 2, 3, 4, 5, 6>);
        std::cout << std::format("lsub_sum<1...10> = {}\n", lsub_sum<1, 2, 3, 4, 5, 6>);
        std::cout << std::format("rsub_sum<1...10> = {}\n", rsub_sum<1, 2, 3, 4, 5, 6>);
        std::cout << std::format("{}\n", (1-(2-(3-(4-(5-(6-0)))))));
        std::cout << std::format("rsub_sum<1, 2, 3, 4> = {}\n", rsub_sum<1, 2, 3, 4>);
        std::cout << std::format("rsub_sum<4, 3, 2, 1> = {}\n", rsub_sum<4, 3, 2, 1>);
    }
}







