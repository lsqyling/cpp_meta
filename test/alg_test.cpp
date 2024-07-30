//
// Created by 10580.
//

#include <iostream>
#include <variant>
#include "catch_amalgamated.hpp"
#include "meta/algorithm.hpp"
#include "meta/meta_ns.hpp"
META_NS_BEGIN
constexpr auto vl = type_list<>;

TEST_CASE("alg-testing")
{
    SECTION("empty vl")
    {
        STATIC_REQUIRE(vl == type_list<>);
        STATIC_REQUIRE(vl.empty());
        STATIC_REQUIRE(concepts::type_list < decltype(vl) >);
    }

    SECTION("append value")
    {
        constexpr auto res = append(vl, _v<1> , _v<2>);
        STATIC_REQUIRE(res == value_list <1, 2>);
        std::cout << "append passed!" << std::endl;
    }
    SECTION("append type") {
        {
            constexpr auto res = vl | append(_t<int>, _t<double>);
            STATIC_REQUIRE(res == type_list<int, double>);
        }
        {
            constexpr auto res = append(vl, _t<int>, _t<double>);
            STATIC_REQUIRE(res == type_list<int, double>);
        }
    }

    SECTION("prepend value")
    {
        auto res = prepend(vl, _v<1> , _v<2>);
        auto res1 = res | prepend(_v<3>, _v<4>);
        STATIC_REQUIRE(res1 == value_list <3, 4, 1, 2>);
        std::cout << "prepend passed!" << std::endl;
    }

    SECTION("concat")
    {
        constexpr auto vl = type_list<long, char, int, double, float>;
        STATIC_REQUIRE(vl == concat(type_list<long, char>, type_list<int, double, float>));
        STATIC_REQUIRE(vl == concat(type_list<long, char>, type_list<int>, type_list<double, float>));
    }
}

TEST_CASE("alg-contain-testing")
{
    SECTION("type level")
    {
         auto vl = type_list<int, char, float, short>;
        STATIC_REQUIRE(contain(vl, _t<int>));
        STATIC_REQUIRE(!contain(vl, _t<long long>));
    }
    SECTION("value level")
    {
        auto vl = value_list<1, 2, 3, 4>;
        STATIC_REQUIRE(contain(vl, _v<2>));
        STATIC_REQUIRE(!contain(vl, _v<0>));
        std::cout << "contain passed!" << std::endl;
    }
}


TEST_CASE("alg-convert_to-testing")
{
    SECTION("value level")
    {
        constexpr auto res = value_list<1, 3, 5, 7, 9>
                             | convert_to<std::index_sequence>();
        STATIC_REQUIRE(res == _t<std::index_sequence<1, 3, 5, 7, 9>>);
    }

    SECTION("type level: tuple")
    {
        constexpr auto res = type_list<int, char, double>
                             | convert_to<std::tuple>();
        STATIC_REQUIRE(res == _t<std::tuple<int, char, double>>);
    }

    SECTION("type level: vector")
    {
        constexpr auto res = type_list<int, std::allocator<int>>
                             | convert_to<std::vector>();
        STATIC_REQUIRE(res == _t<std::vector<int, std::allocator<int>>>);
    }
}


TEST_CASE("convert_from-testing")
{
    SECTION("value level")
    {
         constexpr auto vl = convert_from<std::make_index_sequence<10>>();
        STATIC_REQUIRE(vl == value_list<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>);
    }

    SECTION("type level")
    {
        constexpr auto vl = convert_from<std::tuple<int, char, double>>();
        STATIC_REQUIRE(vl == type_list<int, char, double>);
    }
}

TEST_CASE("alg-fold_left-testing")
{
    SECTION("type level")
    {
         constexpr auto result = type_list<int, float, double>
        | fold_left(type_list<>,
        [](concepts::type_list auto acc, auto elem) { return acc | append(elem); }
        );
        STATIC_REQUIRE(result == type_list<int, float, double>);
    }
}


TEST_CASE("transform-filter-unique-fold-testing")
{
    SECTION("value level")
    {
        constexpr auto res = value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
                             | transform([](auto x) { return _v<x * x>; })
                             | filter([](auto x) { return _v<x < 30>; })
                             | fold_left(_v<0>, [](auto acc, auto n) { return _v<acc + n>; });
        STATIC_REQUIRE(res == 55);
    }


    SECTION("type level: add_pointer_t")
    {
        constexpr auto result = type_list<int, char, long, char, short, float, double>
                                | filter([]<typename T>(type_const<T>) { return _v<sizeof(T) < 4>; })
                                | transform([]<typename T>(type_const<T>) { return _t<std::add_pointer_t<T>>; })
                                | unique()
                                | convert_to<std::variant>();
        STATIC_REQUIRE(result == _t<std::variant<char *, short *>>);
    }
    std::cout << "alg passed!" << std::endl;

}






META_NS_END

































