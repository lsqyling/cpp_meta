//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_META_META_NS_HPP
#define CPP_META_INCLUDE_META_META_NS_HPP
#include <iostream>
#include <iomanip>
#define META_NS meta
#define META_NS_BEGIN namespace META_NS {
#define META_NS_END }
#define info(func) std::cout << std::left << std::setw(30) << #func << "passed!" << "\n"
#endif //CPP_META_INCLUDE_META_META_NS_HPP
