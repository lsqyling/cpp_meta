//
// Created by 10580.
//

#ifndef CPP_META_TEMPLATE_TYPE_LIST_HPP
#define CPP_META_TEMPLATE_TYPE_LIST_HPP


namespace meta {

template<typename T> struct return_{ using type = T; };
struct none;

template<typename ...Ts>
struct type_list
{
    struct is_type_list {};
    using type = type_list;
    static constexpr size_t size = sizeof...(Ts);

    template<typename ...T>
    using append = type_list<Ts..., T...>;

    template<typename ...T>
    using preappend = type_list<T..., Ts...>;

    template<template<typename...> class T>
    using to = T<Ts...>;
};

template<typename T>
concept TypeList = requires {
    typename T::type;
    typename T::is_type_list;
};


// fold
template<TypeList In, typename Init, template<typename, typename> class Op>
struct fold : return_<Init> {};
template<typename Acc,
        template<typename, typename> class Op,
        typename E, typename ...Ts>
struct fold<type_list<E, Ts...>, Acc, Op>
        : fold<type_list<Ts...>, typename Op<Acc, E>::type, Op> {};

template<TypeList In, typename Init, template<typename, typename> class Op>
using fold_t = typename fold<In, Init, Op>::type;

// map or transform
template<TypeList In, template<typename> class F>
struct map;
template<template<typename> class F, typename ...Ts>
struct map<type_list<Ts...>, F> : type_list<typename F<Ts>::type...> {};

template<TypeList In, template<typename> class F>
using map_t = typename map<In, F>::type;

//filter
template<TypeList In, template<typename> class P, TypeList Out = type_list<>>
struct filter : Out {};
template<template<typename> class P, TypeList Out, typename E, typename ...Ts>
struct filter<type_list<E, Ts...>, P, Out> :
        std::conditional_t<P<E>::value,
                filter<type_list<Ts...>, P, typename Out::template append<E>>,
                filter<type_list<Ts...>, P, Out>> {};

template<TypeList In, template<typename> class P, TypeList Out = type_list<>>
using filter_t = typename filter<In, P, Out>::type;


/**************************************************************************************/
/**************************************************************************************/
// alg.
// concat
template<TypeList ...In> struct concat;
template<TypeList ...In>
using concat_t = typename concat<In...>::type;

template<>
struct concat<> : type_list<> {};
template<TypeList I0, TypeList I1, TypeList ...In>
struct concat<I0, I1, In...> : concat_t<concat_t<I0, I1>, In...> {};
template<typename ...Ts0, typename ...Ts1>
struct concat<type_list<Ts0...>, type_list<Ts1...>> : type_list<Ts0..., Ts1...> {};

//elem
template<TypeList In, typename E>
struct elem : std::false_type {};
template<typename ...Ts, typename E>
struct elem<type_list<Ts...>, E> :
        std::bool_constant<(false || ... || std::is_same_v<E, Ts>)> {};

template<TypeList In, typename E>
constexpr bool elem_v = elem<In, E>::value;

//unique
template<TypeList In>
class unique
{
    template<TypeList Acc, typename E>
    using append = std::conditional_t<elem_v<Acc, E>, Acc, typename Acc::template append<E>>;
public:
    using type = fold_t<In, type_list<>, append>;
};
template<TypeList In>
using unique_t = typename unique<In>::type;

//partition
template<TypeList In, template<typename> class P>
class partition
{
    template<typename Arg>
    using notp = std::bool_constant<!P<Arg>::value>;
public:
    struct type
    {
        using satisfied = filter_t<In, P>;
        using rest = filter_t<In, notp>;
    };
};
template<TypeList In, template<typename> class P>
using partition_t = typename partition<In, P>::type;

//sort
template<TypeList In, template<typename,typename> class Cmp>
        struct sort : type_list<> {};

template<template<typename, typename> class Cmp,
        typename Pivot, typename ...Ts>
class sort<type_list<Pivot, Ts...>, Cmp>
{
    template<typename E>
    using less_pivot = Cmp<E, Pivot>;
    using split_list = partition_t<type_list<Ts...>, less_pivot>;

    using small_sorted = typename sort<typename split_list::satisfied, Cmp>::type;
    using bigger_sorted = typename sort<typename split_list::rest, Cmp>::type;
public:
    using type = concat_t<typename small_sorted::template append<Pivot>, bigger_sorted>;
};

template<TypeList In, template<typename, typename> class Cmp>
using sort_t = typename sort<In, Cmp>::type;

//flatten
template<TypeList In>
class flatten
{
    struct impl
    {
        template<typename Acc, typename E>
        struct append : Acc::template append<E> {};
        template<typename Acc, typename ...Ts>
        struct append<Acc, type_list<Ts...>> :
                concat_t<Acc, typename flatten<type_list<Ts...>>::type> {};
    };
    template<typename Acc, typename E>
    using append = typename impl::template append<Acc, E>;
public:
    using type = fold_t<In, type_list<>, append>;
};

template<TypeList In>
using flatten_t = typename flatten<In>::type;


}




#endif
