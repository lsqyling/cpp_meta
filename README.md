## CppMeta
[![License](https://img.shields.io/badge/License-Apache%202.0-green.svg)](https://github.com/lsqyling/tsinghua_dsa/blob/main/LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux-blue)](https://img.shields.io/badge/Platform-Linux-blue)
[![Windows](https://img.shields.io/badge/Windows-blue)](https://img.shields.io/badge/Windows-blue)
[![Language](https://img.shields.io/badge/Language-C%2B%2B20-red)](https://en.cppreference.com/w/cpp/compiler_support/20)

**简介：一个使用*C++20 metaprogramming*模板元技术实现的KV数据表，在编译时能对用户的数据KV类型进行重排，内存占用小，
在嵌入式产品中实现高性能数据表。**

### Part1. KV-table
- 项目结构：include/meta/ | test/meta
- 模板远实现： KV table
- constexpr元编程：KV table
- DSL实现最短路径算法



### Part2. MetaNN[TODO]
- 项目结构：include/meta_nn | test/meta_nn
- 项目说明：基于模板元实现的深度学习框架
- var_type_dict: 异类词典



### Part3. 使用说明
- 1. 下载编译meta库
```shell
git clone https://github.com/lsqyling/meta.git &&
cmake -B build &&
cmake --build build -j4 --config Release --target install 
```
- 2. cmake 使用meta库
```cmake
set(meta_DIR xxx/cpp_meta/install/lib/cmake/meta)
# xxx ---> 命令： echo | pwd 的结果，即你下载的目录路径
find_package(meta REQUIRED)

add_executable(hello main.cpp)
target_link_libraries(hello PRIVATE meta::meta)

```
- 3. testing code
```c++
TEST_CASE("transform-filter-unique-fold-testing")
{
    SECTION("value level")
    {
        constexpr auto res = value_list<1, 2, 3, 4, 5, 6, 7, 8, 9, 10>
                             | transform([](auto x) { return _v<x * x>; })
                             | filter([](auto x) { return _v<x < 30>; })
                             | fold_left(_v<0>, [](auto acc, auto n) { return _v<acc + n>; });
        STATIC_REQUIRE(res == 55);
    }


    SECTION("type level: add_pointer_t")
    {
        constexpr auto result = type_list<int, char, long, char, short, float, double>
                                | filter([]<typename T>(type_const<T>) { return _v<sizeof(T) < 4>; })
                                | transform([]<typename T>(type_const<T>) { return _t<std::add_pointer_t<T>>; })
                                | unique()
                                | convert_to<std::variant>();
        STATIC_REQUIRE(result == _t<std::variant<char *, short *>>);
    }
    info(alg);

}


```
- 4. var_type_dict 
```c++
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


```