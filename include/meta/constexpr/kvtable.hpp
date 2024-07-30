//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_META_CONSTEXPR_KVTABLE_HPP
#define CPP_META_INCLUDE_META_CONSTEXPR_KVTABLE_HPP
#include <algorithm>
#include <bitset>
#include "type_list.hpp"
#include "alg.hpp"

namespace meta {

//<key, ValueType>
template<auto Key, typename ValueType, size_t Dim = 1>
struct entry
{
    using type = ValueType;
    static constexpr auto key = Key;
    static constexpr size_t dim = Dim;
    static constexpr bool is_array = dim > 1;
};
template<auto Key, typename ValueType, size_t Dim>
struct entry<Key, ValueType[Dim]> : entry<Key, ValueType, Dim> {};

namespace concepts {
template<typename E>
concept kventry = requires {
    typename E::type;
    requires std::is_standard_layout_v<typename E::type>;
    requires std::is_trivial_v<typename E::type>;
    { E::key } -> std::convertible_to<size_t >;
    { E::dim } -> std::convertible_to<size_t >;
};
}

consteval bool operator==(concepts::kventry auto el, concepts::kventry auto er)
{
    using el_t = decltype(el)::type;
    using er_t = decltype(er)::type;
    return el.dim == er.dim
    && sizeof(el) == sizeof(er)
    && alignof(el_t) == alignof(er_t);
}

template<auto Key, typename ValueType>
inline constexpr auto entry_v = entry<Key, ValueType>{};

template<concepts::type_list auto entry_list>
class data_table
{
    template<concepts::kventry EH, concepts::kventry ...ET>
    class generic_region
    {
        static constexpr size_t number_of_entry = sizeof...(ET) + 1;
        static constexpr size_t max_size =
                std::max(sizeof(typename EH::type), alignof(typename EH::type)) * EH::dim;

        char data[number_of_entry][max_size];

    public:
        bool get_data(size_t nth_data, void *out, size_t len)
        {

            if (nth_data >= len) [[unlikely]]
                return false;
            std::copy_n(data[nth_data], std::min(len, max_size), reinterpret_cast<char*>(out));
            return true;
        }

        bool set_data(size_t nth_data, const void *value, size_t len)
        {
            if (nth_data >= len) [[unlikely]]
                return false;
            std::copy_n(reinterpret_cast<const char*>(value), std::min(len, max_size), data[nth_data]);
            return true;
        }
    };

    template<typename ...R>
    class regions
    {
        std::tuple<R...> regions_;

        template<size_t I, typename Op>
        bool for_data(Op &&op, size_t index)
        {
            size_t region_idx = index >> 16;
            size_t nth_data = index & 0xffff;
            if (I == region_idx)
                return op(std::get<I>(regions_), nth_data);
            return false;
        }

        template<typename Op, size_t ...Is>
        bool for_data(std::index_sequence<Is...>, Op &&op, size_t index)
        {
            return (... || for_data<Is>(std::forward<Op>(op), index));
        }

    public:
        bool get_data(size_t index, void *out, size_t len)
        {
            auto op = [&](auto &&region, size_t nth_data) {
                return region.get_data(nth_data, out, len);
            };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }
        bool set_data(size_t index, const void *value, size_t len)
        {
            auto op = [&](auto &&region, size_t nth_data) {
                return region.set_data(nth_data, value, len);
            };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }
    };

    template<concepts::pair_const ...KeyWithId>
    struct indexer
    {
        static constexpr size_t index_size = sizeof...(KeyWithId);
        size_t key_to_id[index_size]{};
        std::bitset<index_size> mask;

        constexpr indexer()
        {
            static_assert((... && (KeyWithId::first < index_size)), "Key is out of size");
            ((key_to_id[KeyWithId::first] = KeyWithId::second), ...);
        }
    };

    template<auto...> struct dump;

//    alg
    static consteval concepts::type_list auto group_entries(concepts::type_list auto es)
    {
        if constexpr (es.empty())
            return value_list<>;

        else
        {
            constexpr auto e = get_type<es.head()>{};
            constexpr auto group_result = es | partition(
                    [e]<typename E>(type_const<E>) {
                        return _v<E{} == e>;
                    });
            return group_entries(group_result.second) | prepend(group_result.first);
        }
    }

    static constexpr auto entry_groups = group_entries(entry_list);
    static constexpr auto regions_type = entry_groups
            | transform(
                    [](concepts::type_list auto group) {
                        return group | convert_to<generic_region>();
                    })
            | convert_to<regions>();

    static constexpr auto indexer_type =
            (entry_groups
             | fold_left(make_pair(_v<0>, type_list<>),
                         [](concepts::pair_const auto group_list,
                            concepts::type_list auto group_entries) {
                             constexpr auto res = group_entries
                                                  | fold_left(
                                     make_pair(_v<0>, type_list<>),
                                     [group_list]<typename E>(concepts::pair_const auto inner_group, type_const<E>) {
                                         constexpr auto group_id = group_list.first;
                                         constexpr auto inner_id = inner_group.first;
                                         return make_pair(_v<inner_id + 1>, inner_group.second
                                                                            | append(make_pair(_v<E::key>,
                                                                                               _v<group_id << 16 |
                                                                                                  inner_id>)));
                                     });
                             return make_pair(_v<group_list.first + 1>, concat(group_list.second, res.second));
                         })).second | convert_to<indexer>();

    get_type<regions_type> regions_;
    get_type<indexer_type> indexer_;

public:
    bool get_data(size_t key, void *out, size_t len = -1)
    {
        if (key >= entry_list.size() || !indexer_.mask[key])
            return false;
        return regions_.get_data(indexer_.key_to_id[key], out, len);
    }

    bool set_data(size_t key, const void *value, size_t len = -1)
    {
        if (key >= entry_list.size())
            return false;
        return indexer_.mask[key] =
                       regions_.set_data(indexer_.key_to_id[key], value, len);
    }

    void dump_group_info()
    {
        printf("sizeof datatable = %zu\n", sizeof(data_table));
        printf("sizeof region = %zu\n", sizeof(regions_));
        printf("sizeof indexer = %zu\n", sizeof(indexer_));
        for (size_t k = 0; k < entry_list.size(); ++k)
        {
            printf("key = %zu id = 0x%05zx group = %zu subgroup = %zu\n", k,
                   indexer_.key_to_id[k],
                   indexer_.key_to_id[k] >> 16,
                   indexer_.key_to_id[k] & 0xFFFF);
        }
    }
};
}


#endif //CPP_META_INCLUDE_META_CONSTEXPR_KVTABLE_HPP
