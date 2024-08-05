//
// Created by 10580.
//
#include <iostream>
#include "metann/policy/policy_defines.hpp"
#include "metann/policy/accumulator.hpp"

using namespace metann;


ENUM_TYPE_POLICY_OBJ(padd_accu, acc_policy, accu, add);
ENUM_TYPE_POLICY_OBJ(pmul_accu, acc_policy, accu, mul);

VALUE_POLICY_OBJ(pave, acc_policy, is_ave, true);
VALUE_POLICY_OBJ(pno_ave, acc_policy, is_ave, false);

TYPE_POLICY_TEMPLATE(pvalue_type_is, acc_policy, value);
VALUE_POLICY_TEMPLATE(pave_policy_is, acc_policy, is_ave);





void test_accumulator()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << accumulator<>::eval(arr) << std::endl;
    std::cout << accumulator<pmul_accu, pave>::eval(arr) << std::endl;
    std::cout << accumulator<pmul_accu, pno_ave>::eval(arr) << std::endl;
    std::cout << accumulator<pave, pmul_accu>::eval(arr) << std::endl;
    std::cout << accumulator<padd_accu, pave>::eval(arr) << std::endl;
    std::cout << accumulator<padd_accu, pvalue_type_is<double>, pave_policy_is<true>>::eval(arr) << std::endl;
//    std::cout << accumulator<padd_accu, pmul_accu>::eval(arr) << std::endl;
}






int main(int argc, char *argv[])
{
    test_accumulator();


    return 0;
}