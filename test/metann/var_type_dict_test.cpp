//
// Created by 10580.
//
#include "metann/facilities/var_type_dict.hpp"

using namespace metann;
struct A;
struct B;
struct C;
class weight;

class FParams : public var_type_dict<A, B, C, weight> {};

template<typename In>
float fun(const In &in)
{
    auto a = in.template get<A>();
    auto b = in.template get<B>();
    auto c = in.template get<C>();
    auto w = in.template get<weight>();
    return c * (a * w + b * (1 - w));
}



void test_get_set()
{
    auto r = fun(FParams::create()
                        .set<A>(1.3f)
                        .set<B>(2.4f)
                        .set<C>(3.0f)
                        .set<weight>(0.1f));

    std::cout << "r = " << r << std::endl;

    info(var_type_dict);
}





int main(int argc, char *argv[])
{
    test_get_set();




    return 0;
}