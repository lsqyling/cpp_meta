//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_POLICY_POLICY_DEFINES_HPP
#define CPP_META_INCLUDE_METANN_POLICY_POLICY_DEFINES_HPP
#include "metann/metann_ns.hpp"
#include "metann/facilities/metann_trait.hpp"
METANN_NS_BEGIN

#define ENUM_TYPE_POLICY_OBJ(PolicyName, Ma, Mi, Val)   \
struct PolicyName : virtual public Ma                   \
{                                                       \
    using minor_class = Ma::Mi##_typecate;              \
    using Mi = Ma::Mi##_typecate::Val;                  \
}                                                       \



#define VALUE_POLICY_OBJ(PolicyName, Ma, Mi, Val)           \
struct PolicyName : virtual public Ma                       \
{                                                           \
    using minor_class = Ma::Mi##_valuecate;                 \
private:                                                    \
    using type1 = decltype(Ma::Mi);                         \
    using type2 = remove_const_ref_t<type1>;                \
public:                                                     \
    static constexpr type2 Mi = static_cast<type2>(Val);    \
}                                                           \


#define TYPE_POLICY_TEMPLATE(PolicyName, Ma, Mi)            \
template<typename T>                                        \
struct PolicyName : virtual public Ma                       \
{                                                           \
    using minor_class = Ma::Mi##_typecate;                  \
    using Mi = T;                                           \
}                                                           \


#define VALUE_POLICY_TEMPLATE(PolicyName, Ma, Mi)               \
template<remove_const_ref_t<decltype(Ma::Mi)> T>                \
struct PolicyName : virtual public Ma                           \
{                                                               \
    using minor_class = Ma::Mi##_valuecate;                     \
private:                                                        \
    using type1 = decltype(Ma::Mi);                             \
    using type2 = remove_const_ref_t<type1>;                    \
public:                                                         \
    static constexpr type2 Mi = T;                              \
}                                                               \

METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_POLICY_POLICY_DEFINES_HPP
