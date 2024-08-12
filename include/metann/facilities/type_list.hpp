//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
#include <type_traits>
#include "metann/metann_ns.hpp"
METANN_NS_BEGIN
template<size_t lhs, size_t rhs>
constexpr bool is_less = lhs < rhs;

template<template<typename> class P>
struct negate
{
    template<typename ...Ts>
    using type = std::bool_constant<!P<Ts...>::value>;
};

template<typename T, typename U>
struct is_not_same : std::bool_constant<!std::is_same_v<T, U>> {};

template<typename ...Ts>
struct type_list
{
    struct is_type_list {};
    using type = type_list;

    static constexpr size_t size = sizeof...(Ts);
    template<typename ...Us>
    using append = type_list<Ts..., Us...>;
    template<typename ...Us>
    using prepend = type_list<Us..., Ts...>;
    template<template<typename...> typename T>
    using to = T<Ts...>;
};

template<typename T>
struct type_list_from {};

template<template<typename...> typename T, typename... Ts>
struct type_list_from<T<Ts...>> : type_list<Ts...> {};

template<typename T>
using type_list_from_t = type_list_from<T>::type;

namespace concepts {
template<typename TypeList>
concept type_list = requires {
    typename TypeList::is_type_list;
    typename TypeList::type;
};
}

template<concepts::type_list in>
requires (in::size > 0)
struct head;

template<typename H, typename ...Ts>
struct head<type_list<H, Ts...>>
{
    using type = H;
};

template<concepts::type_list in>
using head_t = head<in>::type;

template<concepts::type_list in>
requires (in::size > 0)
struct tail;

template<typename H, typename ...Ts>
struct tail<type_list<H, Ts...>>
{
    using type = type_list<Ts...>;
};

template<concepts::type_list in>
using tail_t = tail<in>::type;

template<concepts::type_list in>
requires (in::size > 0)
struct last;

template<typename H>
struct last<type_list<H>>
{
    using type = H;
};

template<typename H0, typename H1, typename ...Ts>
struct last<type_list<H0, H1,Ts...>> : last<type_list<H1, Ts...>> {};

template<concepts::type_list in>
using last_t = last<in>::type;



















METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
