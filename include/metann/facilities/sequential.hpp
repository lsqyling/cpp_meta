//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
#include "metann/metann_ns.hpp"
#include "utility.hpp"
METANN_NS_BEGIN

//create
namespace NSCreate {
template<typename L, typename R>
struct concat;

template<template<typename...> class Cont, typename ...L, typename ...R>
struct concat<Cont<L...>, Cont<R...>>
{
    using type = Cont<L..., R...>;
};
}

template<template<typename...> class Cont, typename Param, int N>
struct create
{
    using type = NSCreate::concat<
            typename create<Cont, Param, N/2>::type,
            typename create<Cont, Param, N - N/2>::type
            >::type;
};

template<template<typename...> class Cont, typename Param>
struct create<Cont, Param, 1>
{
    using type = Cont<Param>;
};


template<template<typename...> class Cont, typename Param>
struct create<Cont, Param, 0>
{
    using type = Cont<>;
};

template<template<typename ...> class Cont, typename Param, int N>
using create_t = create<Cont, Param, N>::type;

//At
namespace NSAt {
template<typename Ignore>
struct impl;

template<int...Ignore>
struct impl<utility::index_sequence<Ignore...>>
{
    template<typename Nth>
    static Nth apply(decltype(Ignore, (void *) nullptr)..., Nth *,...);
};
}

template<typename Cont, int N>
struct at;

template<template<typename...> class Cont, typename ...Params, int N>
struct at<Cont<Params...>, N>
{
    using type = decltype(NSAt::impl<utility::make_index_sequence_t<N>>::apply(((Params*)nullptr)...));

};

template<typename Cont, int N>
using at_t = at<Cont, N>::type;

//Order


























METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
