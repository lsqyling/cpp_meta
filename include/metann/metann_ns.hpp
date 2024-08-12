//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_METANN_NS_HPP
#define CPP_META_INCLUDE_METANN_METANN_NS_HPP
#include <iostream>
#include <iomanip>
#define METANN_NS metann
#define METANN_NS_BEGIN namespace METANN_NS {
#define METANN_NS_END }
#define info(func) std::cout << std::left << std::setw(18) << #func << "passed!" << "\n"
#endif //CPP_META_INCLUDE_METANN_METANN_NS_HPP
