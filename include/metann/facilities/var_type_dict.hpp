//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_VAR_TYPE_DICT_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_VAR_TYPE_DICT_HPP
#include <type_traits>
#include <stdexcept>
#include <memory>
#include "metann/metann_ns.hpp"
#include "sequential.hpp"

METANN_NS_BEGIN

struct NullParameter {};


template<typename ...Parameters>
class var_type_dict
{
    template<typename ...Types>
    struct values
    {
        using keys = var_type_dict;
        template<typename Key>
        using value_type = sequential::at_t<values, sequential::order_v<var_type_dict, Key>>;
        template<typename Key>
        static constexpr bool is_value_empty = std::is_same_v<value_type<Key>, NullParameter>;


        values() = default;
        values(values &&val) noexcept
        {
            for (int i = 0; i < sizeof...(Types); ++i)
            {
                m_tuple[i] = std::move(val.m_tuple[i]);
            }
        }
        values(const values &) = default;
        values &operator=(const values &) = default;
        values &operator=(values &&) = default;
        values(std::shared_ptr<void> (&&input)[sizeof...(Types)])
        {
            for (int i = 0; i < sizeof...(Types); ++i)
            {
                m_tuple[i] = std::move(input[i]);
            }
        }

        template<typename Tag, typename ...Params>
        void update(Params &&...params)
        {
            constexpr auto pos = sequential::order_v<var_type_dict, Tag>;
            using raw_type = sequential::at_t<values, pos>;
            auto tmp = new raw_type(std::forward<Params>(params)...);
            m_tuple[pos] = std::shared_ptr<void>(tmp, [](void *ptr) {
                raw_type *p = ptr;
                delete p;
            });
        }

        template<typename Tag, typename Val>
        auto set(Val &&val) &&
        {
            constexpr auto tagpos = sequential::order_v<var_type_dict, Tag>;
            using raw_type = remove_const_ref_t<Val>;
            auto tmp = new raw_type(std::forward<Val>(val));
            m_tuple[tagpos] = std::shared_ptr<void>(tmp, [](void *ptr) {
               auto *p = static_cast<raw_type *>(ptr);
               delete p;
            });
            if constexpr (std::is_same_v<raw_type, sequential::at_t<values, tagpos>>)
            {
                return *this;
            }
            else
            {
                using new_type = sequential::set_t<values, tagpos, raw_type>;
                return new_type(std::move(m_tuple));
            }
        }

        template<typename Tag>
        const auto &get() const
        {
            constexpr auto tagpos = sequential::order_v<var_type_dict, Tag>;
            using aim_type = sequential::at_t<values, tagpos>;
            void *tmp = m_tuple[tagpos].get();
            if (!tmp)
                throw std::runtime_error("Empty value.");
            auto *res = static_cast<aim_type *>(tmp);
            return *res;
        }

        template<typename Tag>
        auto &get()
        {
            constexpr auto tagpos = sequential::order_v<var_type_dict, Tag>;
            using aim_type = sequential::at_t<values, tagpos>;
            void *tmp = m_tuple[tagpos].get();
            if (!tmp)
                throw std::runtime_error("Empty Value.");
            auto *res = static_cast<aim_type *>(tmp);
            return *res;
        }

    private:
        std::shared_ptr<void> m_tuple[(sizeof...(Types) == 0) ? 1 : sizeof...(Types)];


    };

public:
    static auto create()
    {
        using type = sequential::create_t<values, NullParameter, sizeof...(Parameters)>;
        return type{};
    }
};




METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_VAR_TYPE_DICT_HPP
