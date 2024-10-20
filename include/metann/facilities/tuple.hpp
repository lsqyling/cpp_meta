//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_TUPLE_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_TUPLE_HPP
#include "metann/metann_ns.hpp"
#include "metann/facilities/type_list.hpp"
METANN_NS_BEGIN
template<typename T>
struct is_tuple : std::false_type {};

template<>
struct is_tuple<std::tuple<>> : std::true_type {};

template<typename ...Ts>
struct is_tuple<std::tuple<Ts...>> : std::true_type {};

template<typename T>
constexpr bool is_tuple_v = is_tuple<T>::value;

namespace concepts {
template<typename T>
concept tuple = is_tuple_v<T>;
}

template<concepts::tuple ...in>
struct tuple_cat
{
private:
    using cat_type_list = concat_t<type_list_from_t<in>...>;
public:
    using type = typename cat_type_list::template to<std::tuple>;
};

template<concepts::tuple ...in>
using tuple_cat_t = tuple_cat<in...>::type;

template<concepts::tuple in, size_t ...idx>
struct tuple_at
{
    using type = std::tuple<std::tuple_element_t<idx, in>...>;
};

template<concepts::tuple in, size_t ...idx>
using tuple_at_t = tuple_at<in, idx...>::type;

template<concepts::tuple in, typename E>
struct tuple_remove
{
private:
    using remove_type_list = remove_t<type_list_from_t<in>, E>;
public:
    using type = typename remove_type_list::template to<std::tuple>;
};

template<concepts::tuple in, typename E>
using tuple_remove_t = tuple_remove<in, E>::type;



METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_TUPLE_HPP
