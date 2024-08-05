//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
#define CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
#include "metann/metann_ns.hpp"
#include "metann/facilities/metann_trait.hpp"
#include "metann/facilities/sequential.hpp"
METANN_NS_BEGIN

namespace NSPolicySelect {
template<typename PolicyCont>
struct policy_selres;

template<typename CurPolicy, typename ...OtherPolicies>
struct policy_selres<policy_container<CurPolicy, OtherPolicies...>>
        : CurPolicy, OtherPolicies... {};

template<typename MajorClass>
struct major_filter
{
    template<typename State, typename Input>
    using apply = std::conditional_t<
            std::is_same_v<MajorClass, typename Input::major_class>,
            sequential::push_back_t<State, Input>,
            type_identity<State>>;
};

template<typename PolicyCont>
struct minor_check
{
    static constexpr bool value = true;
};

template<typename CurPolicy, typename ...Ps>
struct minor_check<policy_container<CurPolicy, Ps...>>
{
    static constexpr bool cur_check =
            ((!std::is_same_v<typename CurPolicy::minor_class, typename Ps::minor_class>) && ...);
    static constexpr bool value =
            and_value<cur_check, minor_check<policy_container<Ps...>>>;

};

template<typename MajorClass, typename PolicyCont>
struct selector
{
    using t1 = sequential::fold_t<policy_container<>,
            PolicyCont, major_filter<MajorClass>::template apply>;

    static_assert(minor_check<t1>::value, "Minor class set conflict!");

    using type = std::conditional_t<sequential::size_v<t1> == 0, MajorClass, policy_selres<t1>>;
};
}

template<typename MajorClass, typename PolicyCont>
using policy_select_t = NSPolicySelect::selector<MajorClass, PolicyCont>::type;










METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
