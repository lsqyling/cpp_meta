#include <iostream>
#include "catch_amalgamated.hpp"

namespace meta121 {
template<template<typename> class T1, typename T2>
struct fun_
{
    using type = typename T1<T2>::type;
};

template<template<typename> class T1, typename T2>
using fun = fun_<T1, T2>::type;
}

namespace meta122 {
template<bool> struct fun_;
template<>
struct fun_<true>
{
    template<typename T>
    using type = std::add_lvalue_reference<T>;
};
template<>
struct fun_<false>
{
    template<typename T>
    using type = std::remove_reference<T>;
};

template<typename T, bool AddOrRemove>
using fun = typename fun_<AddOrRemove>::template type<T>;

template<typename T>
using res_ = fun<T, false>;
}

namespace meta131 {
template<typename T>
struct remove_reference_const_
{
private:
    using inter_type = typename std::remove_reference<T>::type;
public:
    using type = std::remove_const<inter_type>;
};
}

namespace meta132 {
template<typename TW>
struct wrapper
{
    template<typename T>
    struct fun_
    {
        static constexpr size_t value = 0;
    };
    template<>
    struct fun_<int>
    {
        static constexpr size_t value = 1;
    };
};
}

namespace meta133 {
template<size_t n>
constexpr size_t ones_count = (n & 1) + ones_count<n / 2>;

template<>
constexpr size_t ones_count<0> = 0;

template<size_t ...n>
constexpr size_t accumulate = 0;

template<size_t curr, size_t ...n>
constexpr size_t accumulate<curr, n...> = curr + accumulate<n...>;

template<size_t ...n>
constexpr size_t sum_of = (0 + ... + n);
}

namespace meta134 {
template<size_t n1>
struct wrap_
{
    template<size_t n2>
    struct impl
    {
        static constexpr size_t value = n2 + impl<n2 - 1>::value;
    };
    template<>
    struct impl<0>
    {
        static constexpr size_t value = 0;
    };
    template<size_t n>
    static constexpr size_t value = impl<n1 + n>::value;
};

template<size_t n>
constexpr size_t impl = n + impl<n-1>;
template<>
constexpr size_t impl<0> = 0;

template<size_t ns>
struct wrap_v2
{
    template<size_t n>
    static constexpr size_t value = impl<n + ns>;
};
}

namespace meta135 {

template<size_t n>
constexpr bool is_odd = (n & 1) == 1;

template<bool, typename>
constexpr bool and_v = false;
template<typename T>
constexpr bool and_v<true, T> = T::value;


template<size_t... n> struct all_odd;
template<size_t n0>
struct all_odd<n0>
{
    static constexpr bool value = is_odd<n0>;
};

template<size_t cur, size_t ...n>
struct all_odd<cur,n...>
{
    static constexpr bool value = and_v<is_odd<cur>, all_odd<n...>>;
};
}

namespace meta_167 {

template<typename T>
struct has_type
{
    static constexpr bool value = requires {
        typename T::type;
    };
};

template<typename T>
constexpr bool has_type_v = has_type<T>::value;

template<typename T>
struct node_t
{
    using type = T;
};
template<typename T>
struct node_v
{
    static constexpr bool  value = std::is_arithmetic_v<T>;
};

namespace sfinae {
struct true_type { static constexpr bool value = true; };
struct false_type { static constexpr bool value = false; };

template<typename T, typename = void >
struct has_type : false_type {};

template<typename T>
struct has_type<T, std::void_t<typename T::type>> : true_type {};

template<typename T>
constexpr bool has_type_v = has_type<T>::value;

template<typename T, typename = void>
struct has_value : false_type {};

template<typename T>
struct has_value<T, std::void_t<decltype(T::value)>> : true_type {};

template<typename T>
constexpr bool has_value_v = has_value<T>::value;

}
}


TEST_CASE("simple-meta-func")
{
    SECTION("meta121")
    {
        using namespace meta121;
        STATIC_REQUIRE(std::is_same_v<fun<std::remove_reference, int&>, int>);
    }

    SECTION("meta122")
    {
        using namespace meta122;
        STATIC_REQUIRE(std::is_same_v<res_<int&>::type, int>);
    }

    SECTION("meta132")
    {
        using namespace meta132;
        STATIC_REQUIRE(wrapper<double>::fun_<int>::value == 1);
    }

    SECTION("meta133")
    {
        using namespace meta133;
        STATIC_REQUIRE(ones_count<255> == 8);
        std::cout << std::format("45 has ones totally is: {}\n", ones_count<45>);
        STATIC_REQUIRE(accumulate<1, 2, 3, 4, 5> == 15);
        STATIC_REQUIRE(sum_of<1, 2, 3, 4, 5, 6, 7, 8, 9, 10> == 55);
    }


    SECTION("meta134")
    {
        using namespace meta134;
        STATIC_REQUIRE(wrap_<50>::value<50> == 5050);//bad
        STATIC_REQUIRE(wrap_v2<100>::value<100> == 20100);//good
    }


    SECTION("meta135")
    {
        using namespace meta135;
        STATIC_REQUIRE(all_odd<1, 3, 5, 7, 9, 11, 13, 15>::value);
        STATIC_REQUIRE(all_odd<17, 19, 21, 23, 25, 27, 29, 31, 32>::value == false);
    }


    SECTION("meta_167")
    {
        using namespace meta_167;
        STATIC_REQUIRE(has_type_v<node_t<int>>);
        STATIC_REQUIRE(!has_type_v<node_v<int>>);

        STATIC_REQUIRE(sfinae::has_type_v<node_t<double>>);
        STATIC_REQUIRE(sfinae::has_type_v<node_v<double>> == false);

        STATIC_REQUIRE(sfinae::has_value_v<node_t<double>> == false);
        STATIC_REQUIRE(sfinae::has_value_v<node_v<double>>);
    }
}