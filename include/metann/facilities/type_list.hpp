//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
#include <utility>
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

template<typename TypeValue>
concept type_value = requires {
    TypeValue::type;
    TypeValue::value;
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

template<concepts::type_list in, typename out = type_list<>>
struct drop_last;
template<typename T, typename out>
struct drop_last<type_list<T>, out>
{
    using type = out;
};

template<typename H0, typename H1, typename ...Ts, typename out>
struct drop_last<type_list<H0, H1, Ts...>, out>
        : drop_last<type_list<H1, Ts...>, typename out::template append<H0>> {};

template<concepts::type_list in, typename out = type_list<>>
using drop_last_t = drop_last<in, out>::type;

//alg.
template<concepts::type_list in, template<typename> typename F>
struct map;

template<template<typename> typename F, typename ...Ts>
struct map<type_list<Ts...>, F> : type_list<typename F<Ts>::type...> {};

template<concepts::type_list in, template<typename> typename F>
using map_t = map<in, F>::type;

template<concepts::type_list in, template<typename> class P, concepts::type_list out = type_list<>>
struct filter : out {};

template<template<typename> class P, concepts::type_list out, typename H, typename ...Hs>
struct filter<type_list<H, Hs...>, P, out>
        : std::conditional_t<
                P<H>::value,
                filter<type_list<Hs...>, P, typename out::template append<H>>,
                filter<type_list<Hs...>, P, out>> {};

template<concepts::type_list in, template<typename> class P>
using filter_t = filter<in, P>::type;

template<concepts::type_list in, typename E>
struct remove
{
private:
    template<typename F>
    using is_not_E = is_not_same<F, E>;

public:
    using type = filter_t<in, is_not_E>;
};

template<concepts::type_list in, typename E>
using remove_t = remove<in, E>::type;

template<concepts::type_list in, template<typename> class P>
struct remove_if
{
private:
    template<typename E>
    using not_P = typename negate<P>::template type<E>;
public:
    using type = filter_t<in, not_P>;
};

template<concepts::type_list in, template<typename> class P>
using remove_if_t = remove_if<in, P>::type;

template<typename T>
struct id
{
    using type = T;
};

template<concepts::type_list in, typename init, template<typename, typename> class op>
struct fold : id<init> {};

template<typename acc, template<typename, typename> class op,
        typename H, typename ...Hs>
struct fold<type_list<H, Hs...>, acc, op>
        : fold<type_list<Hs...>, typename op<acc, H>::type, op> {};

template<concepts::type_list in, typename init, template<typename, typename> class op>
using fold_t = fold<in, init, op>::type;


template<concepts::type_list ...>
struct concat;

template<concepts::type_list in>
struct concat<in> : in {};

template<typename ...Ts0, typename ...Ts1>
struct concat<type_list<Ts0...>, type_list<Ts1...>>
        : type_list<Ts0..., Ts1...> {};

template<concepts::type_list in0, concepts::type_list in1, concepts::type_list ...Ls>
struct concat<in0, in1, Ls...> : concat<typename concat<in0, in1>::type, Ls...> {};

template<concepts::type_list ...Ls>
using concat_t = concat<Ls...>::type;

template<concepts::type_list in, typename E>
struct contain : std::false_type {};

template<typename ...Ts, typename E>
struct contain<type_list<Ts...>, E>
        : std::bool_constant<(false || ... || std::is_same_v<Ts, E>)> {};

template<concepts::type_list in, typename E>
constexpr bool contain_v = contain<in, E>::value;

constexpr size_t npos = -1ULL;

namespace detail {
template<concepts::type_list in, typename E, size_t offset>
struct find_impl;

template<typename E, size_t offset>
struct find_impl<type_list<>, E, offset> : std::integral_constant<size_t, npos> {};

template<typename E, typename H, typename ...Ts, size_t offset>
struct find_impl<type_list<H, Ts...>, E, offset>
        : std::conditional_t<
                std::is_same_v<E, H>,
                std::integral_constant<size_t, offset>,
                find_impl<type_list<Ts...>, E, offset+1>> {};


template<concepts::type_list in, template<typename> class P, size_t offset>
struct find_impl_if;

template<template<typename> class P, size_t offset>
struct find_impl_if<type_list<>, P, offset> : std::integral_constant<size_t, npos> {};

template<template<typename> class P,
        typename H, typename ...Ts,
        size_t offset>
struct find_impl_if<type_list<H, Ts...>, P, offset>
        : std::conditional_t<
                P<H>::value,
                std::integral_constant<size_t, offset>,
                find_impl_if<type_list<Ts...>, P, offset + 1>> {};
}

template<concepts::type_list in, typename E>
struct find : detail::find_impl<in, E, 0> {};

template<concepts::type_list in, typename E>
using find_t = find<in, E>::type;

template<concepts::type_list in, typename E>
constexpr size_t find_v = find<in, E>::value;

template<concepts::type_list in, template<typename> class P>
struct find_if : detail::find_impl_if<in, P, 0> {};

template<concepts::type_list in, template<typename> class P>
using find_if_t = find_if<in, P>::type;

template<concepts::type_list in, template<typename> class P>
constexpr size_t find_if_v = find_if<in, P>::value;

template<concepts::type_list in>
struct unique
{
private:
    template<concepts::type_list acc, typename E>
    using add = std::conditional_t<
            contain_v<acc, E>,
            acc,
            typename acc::template append<E>>;
public:
    using type = fold_t<in, type_list<>, add>;
};

template<concepts::type_list in>
using unique_t = unique<in>::type;

template<concepts::type_list in>
struct reverse;

template<>
struct reverse<type_list<>> : type_list<> {};

template<typename T, typename ...Ts>
struct reverse<type_list<T, Ts...>>
        : reverse<type_list<Ts...>>::template append<T> {};

template<concepts::type_list in>
using reverse_t = reverse<in>::type;

template<concepts::type_list in, typename E>
struct count;

template<typename ...Ts, typename E>
struct count<type_list<Ts...>, E>
        : std::integral_constant<size_t, (0 + ... + std::is_same_v<Ts, E>)> {};

template<concepts::type_list in, typename E>
constexpr size_t count_v = count<in, E>::value;

template<concepts::type_list in, size_t idx>
requires (idx < in::size)
struct at;

template<typename H, typename ...Ts>
struct at<type_list<H, Ts...>, 0> : id<H> {};


template<typename H, typename ...Ts, size_t idx>
struct at<type_list<H, Ts...>, idx> : at<type_list<Ts...>, idx - 1> {};

template<concepts::type_list in, size_t idx>
using at_t = at<in, idx>::type;

template<concepts::type_list in, size_t n, typename = std::make_index_sequence<in::size>>
requires (n <= in::size)
struct first_n;

template<typename ...Ts, size_t n, size_t ...Is>
struct first_n<type_list<Ts...>, n, std::index_sequence<Is...>>
        : concat_t<
        std::conditional_t<
        is_less<Is, n>,
        type_list<Ts>,
        type_list<>>...> {};

template<concepts::type_list in, size_t n>
using first_nt = first_n<in, n>::type;

template<concepts::type_list in, typename Old, typename New>
struct replace
{
private:
    template<typename T>
    using substitute = std::conditional<std::is_same_v<T, Old>, New, T>;

public:
    using type = map_t<in, substitute>;
};

template<concepts::type_list in, typename Old, typename New>
using replace_t = replace<in, Old, New>::type;

template<concepts::type_list in0, concepts::type_list in1>
struct union_set
{
    using type = unique_t<concat_t<in0, in1>>;
};

template<concepts::type_list in0, concepts::type_list in1>
using union_set_t = union_set<in0, in1>::type;

template<concepts::type_list in0, concepts::type_list in1>
struct intersection_set
{
private:
    template<typename T>
    using contained = contain<in0, T>;

public:
    using type = filter_t<in1, contained>;
};


template<concepts::type_list in0, concepts::type_list in1>
using intersection_set_t = intersection_set<in0, in1>::type;


template<concepts::type_list in0, concepts::type_list in1>
struct difference_set
{
private:
    template<typename E>
    struct contained : contain<in1, E> {};

public:
    using type = remove_if_t<in0, contained>;
};

template<concepts::type_list in0, concepts::type_list in1>
using difference_set_t = difference_set<in0, in1>::type;

template<concepts::type_list in0, concepts::type_list in1>
struct symmetric_difference_set
{
    using type = concat_t<difference_set_t<in0, in1>, difference_set_t<in1, in0>>;
};

template<concepts::type_list in0, concepts::type_list in1>
using symmetric_difference_set_t = symmetric_difference_set<in0, in1>::type;


template<concepts::type_list in,template<typename> class P, typename out = type_list<type_list<>>>
struct split_if;

template<template<typename> class P, typename out>
struct split_if<type_list<>, P, out>
{
private:
    using noempty = remove_t<out, type_list<>>;
public:
    using type = reverse_t<noempty>;
};

template<template<typename> class P, typename H, typename ...Ts, typename head_list, typename...lists>
struct split_if<type_list<H, Ts...>, P, type_list<head_list, lists...>>
        : std::conditional_t<
                P<H>::value,
                split_if<type_list<Ts...>, P, type_list<type_list<>, head_list, lists...>>,
                split_if<type_list<Ts...>, P, type_list<typename head_list::template append<H>, lists...>>> {};

template<concepts::type_list in, template<typename> class P>
using split_if_t = split_if<in, P>::type;


template<concepts::type_list in, typename delimiter>
struct split
{
private:
    template<typename E>
    using is_delimiter = std::is_same<E, delimiter>;
public:
    using type = split_if_t<in, is_delimiter>;
};

template<concepts::type_list in, typename delimiter>
using split_t = split<in, delimiter>::type;


template<typename T>
struct reverse_sequence;

template<typename T>
struct reverse_sequence<std::integer_sequence<T>>
{
    template<T ...Is>
    using append = std::integer_sequence<T, Is...>;
    using type = std::integer_sequence<T>;
};

template<typename T, T idx, T ...ids>
struct reverse_sequence<std::integer_sequence<T, idx, ids...>>
{
    template<T ...app>
    using append = typename reverse_sequence<
            std::integer_sequence<T, ids...>>::template append<idx, app...>;
    using type = typename reverse_sequence<
            std::integer_sequence<T, ids...>>::template append<idx>;
};

template<typename T>
using reverse_sequence_t = reverse_sequence<T>::type;

template<concepts::type_list T>
struct tuple_size;

template<size_t I, concepts::type_list T>
struct tuple_element;

template<typename ...Ts>
struct tuple_size<type_list<Ts...>> : std::integral_constant<size_t, sizeof...(Ts)> {};

template<size_t I, typename ...Ts>
struct tuple_element<I, type_list<Ts...>>
{
    using type = at_t<type_list<Ts...>, I>;
};

template<concepts::type_list T>
constexpr size_t tuple_size_v = tuple_size<T>::value;

template<size_t I, concepts::type_list T>
using tuple_element_t = tuple_element<I, T>::type;


METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_TYPE_LIST_HPP
