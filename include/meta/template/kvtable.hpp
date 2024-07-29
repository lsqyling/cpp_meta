//
// Created by 10580.
//

#ifndef CPP_META_TEMPLATE_KVTABLE_HPP
#define CPP_META_TEMPLATE_KVTABLE_HPP

#include <bitset>
#include <iostream>
#include <format>
#include "type_list.hpp"

namespace meta {
//<key, ValueType>
template<auto Key, typename ValueType, size_t Dim = 1>
struct entry
{
    static constexpr auto key = Key;
    static constexpr size_t dim = Dim;
    static constexpr bool is_array = dim > 1;
    using type = ValueType;
};
// Partially specialize array types
template<auto Key, typename ValueType, size_t Dim>
struct entry<Key, ValueType[Dim]> : entry<Key, ValueType, Dim> {};

template<typename E>
concept KVEntry = requires {
    typename E::type;
    requires std::is_standard_layout_v<typename E::type>;
    requires std::is_trivial_v<typename E::type>;
    { E::key } -> std::convertible_to<size_t>;
    { E::dim } -> std::convertible_to<size_t>;
};

template<TypeList Es = type_list<>, TypeList Gs = type_list<>>
struct group_entries_trait : Gs {};

template<KVEntry H, KVEntry ...Ts, TypeList Gs>
class group_entries_trait<type_list<H, Ts...>, Gs>
{
    template<KVEntry E>
    using group_prediction = std::bool_constant<
            H::dim == E::dim
            && sizeof(typename H::type) == sizeof(typename E::type)
            && alignof(typename H::type) == alignof(typename E::type)>;

    using group = partition_t<type_list<H, Ts...>, group_prediction>;
    using satisfied = typename group::satisfied;
    using rest = typename group::rest;
public:
    using type = typename group_entries_trait<rest, typename Gs::template append<satisfied >>::type;
};

template<TypeList Es = type_list<>, TypeList Gs = type_list<>>
using group_entries_trait_t = group_entries_trait<Es, Gs>::type;

template<TypeList Gs>
class group_index_trait
{
    template<size_t GroupIdx = 0, size_t InnerIdx = 0, TypeList Res = type_list<>>
    struct index
    {
        static constexpr size_t group_index = GroupIdx;
        static constexpr size_t inner_index = InnerIdx;
        using result = Res;
    };

    template<typename Acc, TypeList G>
    class add_group
    {
        static constexpr size_t group_index = Acc::group_index;
        template<typename Acc_, KVEntry E>
        class add_key
        {
            static constexpr size_t inner_index = Acc_::inner_index;
            struct key_with_index
            {
                static constexpr auto key = E::key;
                static constexpr auto id = (group_index << 16) | inner_index;
            };
            using result = typename Acc_::result::template append<key_with_index>;
        public:
            using type = index<group_index + 1, inner_index + 1, result>;
        };
        using result = typename Acc::result;
    public:
        using type = fold_t<G, index<group_index + 1, 0, result>, add_key>;
    };

public:
    using type = typename fold_t<Gs, index<>, add_group>::result;
};

template<TypeList G>
using group_index_trait_t = typename group_index_trait<G>::type;

template<TypeList Es>
class data_table
{
    template<KVEntry H, KVEntry ...Ts>
    class generic_region
    {
        static constexpr size_t number_of_entries = sizeof...(Ts) + 1;
        static constexpr size_t max_size =
                std::max(alignof(typename H::type), sizeof(typename H::type)) * H::dim;
        char data[number_of_entries][max_size];

    public:
        bool get_data(size_t nth_data, void *out, size_t len)
        {
            if (nth_data >= number_of_entries)
                return false;
            std::copy_n(data[nth_data], std::min(len, max_size), reinterpret_cast<char*>(out));
            return true;
        }

        bool set_data(size_t nth_data, const void *value, size_t len)
        {
            if (nth_data >= number_of_entries)
                return false;
            std::copy_n(reinterpret_cast<const char *>(value), std::min(len, max_size), data[nth_data]);
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

        template<size_t ...Is, typename Op>
        bool for_data(std::index_sequence<Is...>, Op &&op, size_t index)
        {
            return (for_data<Is>(std::forward<Op>(op), index) || ...);
        }

    public:
        bool get_data(size_t index, void *out, size_t len)
        {
            auto op = [&](auto &region, size_t nth_data) {
                return region.get_data(nth_data, out, len);
            };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }

        bool set_data(size_t index, const void *value, size_t len)
        {
            auto op = [&](auto &region, size_t nth_data) {
                return region.set_data(nth_data, value, len);
            };
            return for_data(std::make_index_sequence<sizeof...(R)>{}, op, index);
        }
    };

    template<TypeList Gs>
    class generic_region_trait
    {
        template<TypeList G>
        using to_region = return_<typename G::template to<generic_region>>;
    public:
        using type = map_t<Gs, to_region>;
    };

    template<TypeList Gs>
    using generic_region_trait_t = typename generic_region_trait<Gs>::type ;

    template<typename ...Indexes>
    struct indexer
    {
        size_t key_to_id[sizeof...(Indexes)]{};
        std::bitset<sizeof...(Indexes)> mask;
        constexpr indexer()
        {
            constexpr size_t index_size = sizeof...(Indexes);
            static_assert((true && ... && (Indexes::key < index_size)), "key is out of size");
            ((key_to_id[Indexes::key] = Indexes::id), ...);
        }
    };

    using Gs = group_entries_trait_t<Es>;
    using RegionClass = typename generic_region_trait_t<Gs>::template to<regions>;
    using IndexerClass = typename group_index_trait_t<Gs>::template to<indexer>;

    RegionClass region_class{};
    IndexerClass indexer_class{};

public:
    bool get_data(size_t key, void *out, size_t len)
    {
        if (key >= Es::size || !indexer_class.mask[key])
            return false;
        return region_class.get_data(indexer_class.key_to_id[key], out, len);
    }

    bool set_data(size_t key, const void *value, size_t len = -1)
    {
        if (key >= Es::size)
            return false;
        return indexer_class.mask[key] = region_class.set_data(indexer_class.key_to_id[key], value, len);
    }

    void dump_group_info()
    {
        std::cout << std::format("sizeof data_table = {}\n"
                                 "sizeof region = {}\n"
                                 "sizeof indexer = {}\n",
                                 sizeof(data_table),
                                 sizeof(region_class),
                                 sizeof(indexer_class));
        for (size_t k = 0; k < Es::size; ++k)
        {
            std::cout << std::format("key = {}, id = {:#x}, subgroup = {}\n",
                                     indexer_class.key_to_id[k],
                                     indexer_class.key_to_id[k] >> 16,
                                     indexer_class.key_to_id[k] & 0xffff);
        }


    }


























};










}

















#endif
