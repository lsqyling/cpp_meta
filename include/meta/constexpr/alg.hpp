//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_META_CONSTEXPR_ALG_HPP
#define CPP_META_INCLUDE_META_CONSTEXPR_ALG_HPP
#include "type_list.hpp"

namespace meta {
//append
inline constexpr auto append = pipe_adapter(
        []<concepts::value_or_type E,
           concepts::value_or_type ...Es,
           typename ...Ts>(type_list_<Ts...> vl, E, Es...)
           -> type_list_<Ts..., E, Es...> { return {}; }
        );

//prepend
inline constexpr auto prepend = pipe_adapter(
        []<concepts::value_or_type E,
           concepts::value_or_type ...Es,
           typename ...Ts>(type_list_<Ts...> vl, E, Es...)
           -> type_list_<E, Es..., Ts...> { return {}; }
        );

//concat
template<typename ...L, typename ...R>
consteval auto concat(type_list_<L...>, type_list_<R...>)
-> type_list_<L..., R...> { return {}; }

template<concepts::type_list L0, concepts::type_list L1, concepts::type_list ...Rests>
requires (sizeof...(Rests) > 0)
consteval concepts::type_list auto concat(L0 l0, L1 l1, Rests ...rests)
{
    return concat(concat(l0, l1), rests...);
}

//contain
namespace detail {
template<typename E, typename ...Ts>
using contain_impl = value_const<(... || std::same_as<E, Ts>)>;
}

template<typename ...Ts, typename E>
consteval auto contain(type_list_<Ts...>, E)
-> detail::contain_impl<E, Ts...> { return {}; }

//convert_to
namespace detail {
template<template<auto...> class Target>
struct convert_to_target_values
{
    template<concepts::type_const ...Types>
    consteval concepts::type_const auto operator()(type_list_<Types...>) const
    {
        return _t<Target<Types::type...>>;
    }

    template<concepts::value_const ...Values>
    consteval concepts::type_const auto operator()(type_list_<Values...>) const
    {
        return _t<Target<Values::value...>>;
    }
};

template<template<typename...> class Target>
struct convert_to_target_types
{
    template<concepts::type_const ...Types>
    consteval concepts::type_const auto operator()(type_list_<Types...>) const
    {
        return _t<Target<typename Types::type...>>;
    }

    template<typename...Types>
    consteval concepts::type_const auto operator()(type_list_<Types...>) const
    {
        return _t<Target<Types...>>;
    }
};
}

template<template<auto...> class Target>
consteval auto convert_to()
{
    return detail::convert_to_target_values<Target>{};
}

template<template<typename...> class Target>
consteval auto convert_to()
{
    return detail::convert_to_target_types<Target>{};
}

//convert from
namespace detail {
template<typename T> struct convert_from;

template<template<auto...> class Target, auto...Values>
struct convert_from<Target<Values...>>
{
    consteval concepts::type_list auto operator()() const
    {
        return value_list<Values...>;
    }
};

template<template<typename T, T...> class Target, typename T, auto ...Values>
struct convert_from<Target<T, Values...>>
{
    consteval concepts::type_list auto operator()() const
    {
        return value_list<static_cast<T>(Values)...>;
    }
};

template<template<typename...> class Target, typename ...Ts>
struct convert_from<Target<Ts...>>
{
    consteval concepts::type_list auto operator()() const
    {
        return type_list<Ts...>;
    }
};
}

template<typename T>
inline constexpr auto convert_from = detail::convert_from<T>{};

//fold_left
namespace detail {
template<typename Op, typename Acc, typename ...Ts>
struct fold_impl : std::type_identity<Acc> {};

template<typename Op, typename Acc, typename T, typename ...Ts>
struct fold_impl<Op, Acc, T, Ts...> : fold_impl<Op, std::invoke_result_t<Op, Acc, T>, Ts...> {};

template<typename Op, typename Acc, typename ...Ts>
using fold_t = typename fold_impl<Op, Acc, Ts...>::type;
}

inline constexpr auto fold_left = pipe_adapter(
        []<typename Op, typename Acc, typename ...Ts>(type_list_<Ts...>, Acc, Op)
        -> detail::fold_t<Op, Acc, Ts...> { return {}; }
        );

//transform

inline constexpr auto transform = pipe_adapter(
        []<typename F, typename ...Ts>(type_list_<Ts...>, F)
        -> type_list_<std::invoke_result_t<F, Ts>...> { return {}; }
        );

//filter
template<typename P, typename E>
requires concepts::value_const<std::invoke_result_t<P, E>>
inline constexpr bool is_pred_satisfied = std::same_as<value_const<true>,
        std::invoke_result_t<P, E>>;

namespace detail {
template<typename P, typename Result, typename ...Ts>
struct filter_impl : std::type_identity<Result> {};

template<typename P, typename ...Res, typename H, typename ...Ts>
struct filter_impl<P, type_list_<Res...>, H, Ts...>
        : std::conditional_t<is_pred_satisfied<P, H>,
                filter_impl<P, type_list_<Res..., H>, Ts...>,
                filter_impl<P, type_list_<Res...>, Ts...>> {};

template<typename P, typename ...Ts>
using filter_t = detail::filter_impl<P, type_list_<>, Ts...>::type;
}

inline constexpr auto filter = pipe_adapter(
        []<typename P, typename ...Ts>(type_list_<Ts...>, P)
        -> detail::filter_t<P, Ts...> { return {}; }
        );

//unique
namespace detail {
template<typename Result, typename ...Ts>
struct unique_impl : std::type_identity<Result> {};

template<typename ...Res, typename T, typename ...Ts>
struct unique_impl<type_list_<Res...>, T, Ts...>
        : std::conditional_t<detail::contain_impl<T, Res...>::value,
        unique_impl<type_list_<Res...>, Ts...>,
        unique_impl<type_list_<Res..., T>, Ts...>> {};

template<typename ...Ts>
using unique_t = unique_impl<type_list_<>, Ts...>::type;
}

inline constexpr auto unique = pipe_adapter(
        []<typename ...Ts>(type_list_<Ts...>)
        -> detail::unique_t<Ts...> { return {}; }
        );

//partition
namespace detail {
template<typename P, typename Result, typename ...Ts>
struct partition_impl : std::type_identity<Result> {};

template<typename P, typename ...S, typename ...R, typename T, typename ...Ts>
struct partition_impl<P, pair<type_list_<S...>, type_list_<R...>>, T, Ts...>
        : std::conditional_t<is_pred_satisfied<P, T>,
        partition_impl<P, pair<type_list_<S..., T>, type_list_<R...>>, Ts...>,
        partition_impl<P, pair<type_list_<S...>, type_list_<R..., T>>, Ts...>> {};

template<typename P, typename ...Ts>
using partition_t = typename partition_impl<P, pair<type_list_<>, type_list_<>>, Ts...>::type;
}

inline constexpr auto partition = pipe_adapter(
        []<typename P, typename ...Ts>(type_list_<Ts...>, P)
        -> detail::partition_t<P, Ts...> { return {}; }
        );





}



#endif //CPP_META_INCLUDE_META_CONSTEXPR_ALG_HPP
