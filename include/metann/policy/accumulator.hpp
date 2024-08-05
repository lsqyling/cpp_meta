//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_POLICY_ACCUMULATOR_HPP
#define CPP_META_INCLUDE_METANN_POLICY_ACCUMULATOR_HPP
#include <utility>
#include "metann/metann_ns.hpp"
#include "policy_container.hpp"
#include "policy_op.hpp"
#include "policy_defines.hpp"
#include "metann/facilities/metann_trait.hpp"
METANN_NS_BEGIN

struct acc_policy
{
    using major_class = acc_policy;

    struct accu_typecate
    {
        struct add;
        struct mul;
    };
    using accu = accu_typecate::add;
    struct is_ave_valuecate;
    static constexpr bool is_ave = false;
    struct value_typecate;
    using value = double;
};

template<typename ...Policies>
struct accumulator
{
    using policont = policy_container<Policies...>;
    using policy_res = policy_select_t<acc_policy, policont>;

    using value_type = policy_res::value;
    static constexpr bool is_ave = policy_res::is_ave;
    using accu_type = typename policy_res::accu;

    template<typename In>
    static constexpr auto eval(const In &in)
    {
        if constexpr (std::same_as<accu_type, acc_policy::accu_typecate::add>)
        {
            value_type count = 0;
            value_type res = 0;

            for (const auto &x : in)
            {
                res += x;
                ++count;
            }
            if constexpr (is_ave)
                return res / count;
            else
                return res;
        }
        else if constexpr (std::same_as<accu_type, acc_policy::accu_typecate::mul>)
        {
            value_type count = 0;
            value_type res = 1;
            for (const auto &x : in)
            {
                res *= x;
                ++count;
            }
            if constexpr (is_ave)
                return res / count;
            else
                return res;
        }
        else
        {
//            static_assert(dependency_false<accu_type>);
        }
    }
};






METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_POLICY_ACCUMULATOR_HPP
