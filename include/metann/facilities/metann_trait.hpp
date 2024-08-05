//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
#include <utility>
#include "metann/metann_ns.hpp"
METANN_NS_BEGIN

template<typename T>
using remove_const_ref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<typename ...T>
constexpr bool dependency_false = false;

template<typename T>
struct type_identity
{
    using type = T;
};

//or
template<bool cur, typename Next>
constexpr bool or_value = true;
template<typename Next>
constexpr bool or_value<false, Next> = Next::value;

//and
template<bool cur, typename Next>
constexpr bool and_value = false;
template<typename Next>
constexpr bool and_value<true, Next> = Next::value;

//compile switch
template<typename BooleanCont, typename FunCont>
struct compile_time_switch;

template<bool CurBool, bool ...Bools,
        template<typename...> typename FunCont, typename CurFun, typename ...Funs>
struct compile_time_switch<std::integer_sequence<bool, CurBool, Bools...>,
        FunCont<CurFun, Funs...>>
{
    static_assert(sizeof...(Bools) == sizeof...(Funs)
                  || sizeof...(Bools) + 1 == sizeof...(Funs));

    using type = std::conditional_t<CurBool,
            type_identity<CurFun>,
            compile_time_switch<std::integer_sequence<bool, Bools...>, FunCont<Funs...>>
    >::type;
};

template<template<typename> typename FunCont, typename CurFun>
struct compile_time_switch<std::integer_sequence<bool>, FunCont<CurFun>>
{
    using type = CurFun;
};



METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
