//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_DATA_TRAITS_HPP
#define CPP_META_INCLUDE_METANN_DATA_TRAITS_HPP
#include <type_traits>
#include <iterator>
#include "category_tags.hpp"
#include "device_tag.hpp"
METANN_NS_BEGIN

template<typename T>
struct is_iterator
{
    template<typename R>
    static std::true_type test(typename std::iterator_traits<R>::iterator_category *);

    template<typename R>
    static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T>
constexpr bool is_iterator_v = is_iterator<T>::value;

namespace concepts {
template<typename T>
concept is_valid_category = requires {
    typename T::category_tag;
    requires is_valid_category_tag<T>;
};
}

template<concepts::is_valid_category T1, concepts::is_valid_category T2>
constexpr bool operator==(const T1 &t1, const T2 &t2)
{
    if constexpr (!std::is_same_v<T1, T2>)
    {
        return false;
    }
    else
    {
        return t1 == t2;
    }
}

template<concepts::is_valid_category T1, concepts::is_valid_category T2>
constexpr bool operator!=(const T1 &t1, const T2 &t2)
{
    if constexpr (std::is_same_v<T1, T2>)
    {
        return !(t1 == t2);
    }
    else
    {
        return true;
    }
}

template <typename Data>
using shape_type = remove_const_ref_t<decltype(std::declval<Data>().shape())>;

















METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_DATA_TRAITS_HPP
