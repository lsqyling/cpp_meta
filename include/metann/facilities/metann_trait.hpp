//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
#include "metann/metann_ns.hpp"
METANN_NS_BEGIN

template<typename T>
using remove_const_ref_t = std::remove_cv_t<std::remove_reference_t<T>>;










METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_METANN_TRAIT_HPP
