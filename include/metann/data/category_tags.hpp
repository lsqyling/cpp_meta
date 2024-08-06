//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_DATA_CATEGORY_TAGS_HPP
#define CPP_META_INCLUDE_METANN_DATA_CATEGORY_TAGS_HPP
#include "metann/metann_ns.hpp"
#include "metann/facilities/metann_trait.hpp"
METANN_NS_BEGIN
// data types
namespace category_tags {
struct outof_category;

template<size_t Dim>
struct tensor
{
    static constexpr size_t dim_num = Dim;
};

using scalar = tensor<0>;
using vector = tensor<1>;
using matrix = tensor<2>;
}

template<typename T>
constexpr bool is_valid_category_tag = false;
template<size_t Dim>
constexpr bool is_valid_category_tag<category_tags::tensor<Dim>> = true;

template<typename Elem, typename Device, size_t Dim> class tensor;
template<typename Elem, typename Device, size_t Dim>
struct principal_data_type
{
    using type = tensor<Elem, Device, Dim>;
};

template<typename Category, typename Elem, typename Device>
using principal_data_type_t = principal_data_type<Elem, Device, Category::dim_num>::type;

template<typename T>
struct data_category
{
    template<typename R>
    static typename R::category_tag test(typename R::category_tag *);
    template<typename R>
    static typename R::outof_category test(...);

    using type = decltype(test<remove_const_ref_t<T>>(nullptr));
};

template<typename T>
using data_category_t = data_category<T>::type;

template<typename T, size_t Dim>
constexpr bool is_tensor_with = std::is_same_v<data_category_t<T>, category_tags::tensor<Dim>>;

template<typename T>
constexpr bool is_scalar = is_tensor_with<T, 0>;
template<typename T>
constexpr bool is_vector = is_tensor_with<T, 1>;
template<typename T>
constexpr bool is_matrix = is_tensor_with<T, 2>;
template<typename T>
constexpr bool is_threed_array = is_tensor_with<T, 3>;







METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_DATA_CATEGORY_TAGS_HPP
