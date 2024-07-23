## CppMeta
[![License](https://img.shields.io/badge/License-Apache%202.0-green.svg)](https://github.com/lsqyling/tsinghua_dsa/blob/main/LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux-blue)](https://img.shields.io/badge/Platform-Linux-blue)
[![Windows](https://img.shields.io/badge/Windows-blue)](https://img.shields.io/badge/Windows-blue)
[![Language](https://img.shields.io/badge/Language-C%2B%2B20-red)](https://en.cppreference.com/w/cpp/compiler_support/20)

**简介: A KV data table used in embedded products, which is efficiently implemented using C++ metaprogramming. **

### Part1. KV-table
- 项目结构：include/meta/ | test/meta
- 模板远实现： KV table
- constexpr元编程：KV table
- DSL实现最短路径算法



### Part2. MetaNN
- 项目结构：include/meta_nn | test/meta_nn
- 项目说明：基于模板元实现的深度学习框架



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
#include <iostream>
#include <dsa/Vector.h>
#include <dsa/CommonHeaders.h>
#include <dsa/String.h>

using namespace linear;

int main()
{
    Vector<int> v1;
    cout << v1 << endl;

    Vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "vi: " << vi << endl;

    Vector<int> v2(vi);
    cout << "v2: " << v2 << endl;

    Vector<int> v3(std::move(vi));
    cout << "v3: " << v3 << endl;

    Vector<int> v4(10, 1);
    cout << "v4: " << v4 << endl;

    auto beg = v3.begin(), end = v3.end();
    Vector<int> v5(beg, end);
    cout << "v5: " << v5 << endl;

    int i = 2;
    Vector<int> v6(10, i);
    cout << "v6: " << v6 << endl;
    cout << "v6 is empty? " << v6.empty() << endl;

    cout << (v6 == v5) << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

```