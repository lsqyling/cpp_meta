//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_POLICY_POLICY_CONTAINER_HPP
#define CPP_META_INCLUDE_METANN_POLICY_POLICY_CONTAINER_HPP
#include "metann/metann_ns.hpp"
METANN_NS_BEGIN
template<typename ...Policies>
struct policy_container;

template<typename T>
constexpr bool is_policy_container = false;
template<typename ...T>
constexpr bool is_policy_container<policy_container<T...>> = true;

template<typename LayerName, typename ...Policies>
struct subpolicy_container;

template<typename T>
constexpr bool is_subpolicy_container = false;

template<typename Layer, typename ...T>
constexpr bool is_subpolicy_container<subpolicy_container<Layer, T...>> = true;






METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_POLICY_POLICY_CONTAINER_HPP
