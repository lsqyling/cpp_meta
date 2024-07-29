//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_META_CONSTEXPR_TYPE_LIST_HPP
#define CPP_META_INCLUDE_META_CONSTEXPR_TYPE_LIST_HPP
#include <utility>
#include "type_value_c.hpp"


namespace meta {
template<typename ...Ts>
struct type_list_
{
    [[nodiscard]]
    constexpr size_t size() const { return sizeof...(Ts); }
    [[nodiscard]]
    constexpr bool empty() const { return sizeof...(Ts) == 0; }
    constexpr auto head() const requires(sizeof...(Ts) > 0)
    {
        return std::get<0>(std::make_tuple(Ts{}...));
    }
    constexpr auto tail() const requires(sizeof...(Ts) > 0)
    {
        return []<typename T, typename ...Rest>(T, Rest...)
        {
            return type_list_<Rest...>{};
        }(Ts{}...);
    }

    static constexpr bool is_type_list = true;
};

//type_const
template<typename T>
struct type_const
{
    using type = T;
    static constexpr bool is_type_const = true;
};

template<concepts::type_const auto t>
using get_type = typename decltype(t)::type;

template<typename L, typename R>
constexpr bool operator==(type_const<L>, type_const<R>)
{
    return std::same_as<L, R>;
}

template<typename T>
inline constexpr type_const<T> _t;

//value_const
template<auto v>
struct value_const
{
    consteval value_const() = default;

    static constexpr bool is_value_const = true;
    static constexpr auto value = v;

    consteval operator decltype(v)() const
    {
        return v;
    }
};

template<auto value>
inline constexpr value_const<value> _v;

template<auto a, auto b>
constexpr bool operator==(value_const<a>, value_const<b>)
{
    return a == b;
}

//dispatch_value
template<auto v>
struct dispatch_value_
{
    using type = value_const<v>;
};
template<concepts::value_const auto vc>
struct dispatch_value_<vc> : dispatch_value_<vc.value> {};

template<concepts::type_list auto ts>
struct dispatch_value_<ts>
{
    using type = std::decay_t<decltype(ts)>;
};

template<auto value>
using dispatch_value = typename dispatch_value_<value>::type;

template<typename ...Ts>
inline constexpr auto type_list = type_list_<type_const<Ts>...>{};
template<auto ...values>
inline constexpr auto value_list = type_list_<dispatch_value<values>...>{};

template<typename ...lhs, typename ...rhs>
constexpr bool operator==(type_list_<lhs...>, type_list_<rhs...>)
{
    if constexpr (sizeof...(lhs) != sizeof...(rhs))
        return false;
    else
        return ((lhs{} == rhs{}) && ...);
}


//pair
template<typename F, typename S>
struct pair
{
    static constexpr F first{};
    static constexpr S second{};
    static constexpr bool is_pair_const = true;
};

template<typename F, typename S>
consteval auto make_pair(F, S) -> pair<F, S>
{
    return {};
}

template<typename FL, typename SL, typename FR, typename SR>
constexpr bool operator==(pair<FL, SL>, pair<FR, SR>)
{
    return std::same_as<FL, FR> && std::same_as<SL, SR>;
}

//pipe adapter
template<typename Fn>
struct pipe_adapter : private Fn
{
    consteval pipe_adapter(Fn) {}
    template<typename ...Args>
    requires std::invocable<Fn, type_list_<>, Args...>
    consteval auto operator()(Args ...args) const
    {
        return [=, this](concepts::type_list auto vl) {
            return static_cast<const Fn &>(*this)(vl, args...);
        };
    }
    using Fn::operator();
};

template<concepts::type_list VL, typename Adapter>
consteval auto operator|(VL vl, Adapter adapter)
{
    return adapter(vl);
}



}




#endif //CPP_META_INCLUDE_META_CONSTEXPR_TYPE_LIST_HPP
