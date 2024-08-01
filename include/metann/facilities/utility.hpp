//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_UTILITY_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_UTILITY_HPP
#include "metann/metann_ns.hpp"

METANN_NS_BEGIN
namespace utility {
//int_
template<auto i>
struct int_
{
    static constexpr auto value = i;
};

//make_index_sequence
template<int ...Is>
struct index_sequence {};

namespace NSIndexSequence {

template<typename T, typename R>
struct concat;

template<int ...Ls, int ...Rs>
struct concat<index_sequence<Ls...>, index_sequence<Rs...>>
{
    using type = index_sequence<Ls..., (sizeof...(Ls) + Rs)...>;
};
}

template<int N>
struct make_index_sequence
{
    using type = NSIndexSequence::concat<
            typename make_index_sequence<N / 2>::type,
            typename make_index_sequence<N - N / 2>::type
    >::type;
};

template<>
struct make_index_sequence<1>
{
    using type = index_sequence<0>;
};
template<>
struct make_index_sequence<0>
{
    using type = index_sequence<>;
};

template<int N>
using make_index_sequence_t = make_index_sequence<N>::type;

//kvbinder
template<typename K, typename V>
struct kvbinder
{
    using key_type = K;
    using value_type = V;

    static V apply(K *);
};

//when
template<bool b>
struct when;

//value seq
template<typename ...Values>
struct value_sequence;

//pair
template<typename F, typename S>
struct pair
{
    using first_type = F;
    using second_type = S;
};







}
METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_UTILITY_HPP
