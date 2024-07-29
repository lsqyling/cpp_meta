//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_META_CONSTEXPR_TYPE_VALUE_C_HPP
#define CPP_META_INCLUDE_META_CONSTEXPR_TYPE_VALUE_C_HPP
#include <concepts>


namespace meta::concepts {

template<typename T>
concept type_list = requires (T list) {
    requires T::is_type_list;
};

template<typename T>
concept type_const = requires {
    requires T::is_type_const;
};

template<typename T>
concept value_const = requires {
    requires T::is_value_const;
};

template<typename T>
concept pair_const = requires {
    requires T::is_pair_const;
};

template<typename T>
concept value_or_type = (type_list<T> || type_const<T> || value_const<T> || pair_const<T>);


}




#endif //CPP_META_INCLUDE_META_CONSTEXPR_TYPE_VALUE_C_HPP
