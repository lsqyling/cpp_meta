//
// Created by 10580.
//
#include "metann/policy/policy_container.hpp"
#include "metann/policy/policy_op.hpp"
#include "metann/policy/policy_defines.hpp"

using namespace metann;

struct LayerO;


void test_policy_container()
{
    static_assert(is_policy_container<policy_container<int, double>>);
    static_assert(is_policy_container<policy_container<>>);
    static_assert(is_policy_container<int> == false);

    static_assert(is_subpolicy_container<int> == false);
    static_assert(is_subpolicy_container<subpolicy_container<LayerO, int, double>>);
}








int main(int argc, char *argv[])
{
    test_policy_container();



    return 0;
}



