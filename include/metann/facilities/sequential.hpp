//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
#define CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
#include "metann/metann_ns.hpp"
#include "utility.hpp"
#include "metann_trait.hpp"
METANN_NS_BEGIN
namespace sequential {

//create
namespace NSCreate {
template<typename L, typename R>
struct concat;

template<template<typename...> class Cont, typename ...L, typename ...R>
struct concat<Cont<L...>, Cont<R...>>
{
    using type = Cont<L..., R...>;
};
}

template<template<typename...> class Cont, typename Param, int N>
struct create
{
    using type = NSCreate::concat<
            typename create<Cont, Param, N / 2>::type,
            typename create<Cont, Param, N - N / 2>::type
    >::type;
};

template<template<typename...> class Cont, typename Param>
struct create<Cont, Param, 1>
{
    using type = Cont<Param>;
};


template<template<typename...> class Cont, typename Param>
struct create<Cont, Param, 0>
{
    using type = Cont<>;
};

template<template<typename ...> class Cont, typename Param, int N>
using create_t = create<Cont, Param, N>::type;

//At
namespace NSAt {
template<typename Ignore>
struct impl;

template<int...Ignore>
struct impl<utility::index_sequence<Ignore...>>
{
    template<typename Nth>
    static Nth apply(decltype(Ignore, (void *) nullptr)..., Nth *, ...);
};
}

template<typename Cont, int N>
struct at;

template<template<typename...> class Cont, typename ...Params, int N>
struct at<Cont<Params...>, N>
{
    using type = decltype(NSAt::impl<utility::make_index_sequence_t<N>>::apply(((Params *) nullptr)...));

};

template<typename Cont, int N>
using at_t = at<Cont, N>::type;

//Order
namespace NSOrder {
template<typename IndexSeq, typename Cont>
struct impl;

template<template<typename ...> class Cont, typename ...Ts, int ...index>
struct impl<utility::index_sequence<index...>, Cont<Ts...>>
        : utility::kvbinder<Ts, utility::int_<index>> ...
{
    using utility::kvbinder<Ts, utility::int_<index>>::apply...;
};
}

template<typename Cont, typename Req>
struct order;

template<template<typename...> typename Cont, typename ...Params, typename Req>
struct order<Cont<Params...>, Req>
{
    using index_seq = utility::make_index_sequence_t<sizeof...(Params)>;
    using looking_up_table = NSOrder::impl<index_seq, Cont<Params...>>;
    using aim_type = decltype(looking_up_table::apply((Req *) nullptr));
    static constexpr int value = aim_type::value;
};

template<typename Cont, typename Req>
constexpr int order_v = order<Cont, Req>::value;

//set
namespace NSSet {
template<typename Cont, int N, typename Value, typename Remain, typename = utility::when<true>>
struct impl;

template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed, typename T0, typename ...Remain>
struct impl<Cont<Processed...>, N, Value, Cont<T0, Remain...>, utility::when<(N == 0)>>
{
    using type = Cont<Processed..., Value, Remain...>;
};

template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed, typename T0, typename T1, typename ...Remain>
struct impl<Cont<Processed...>, N, Value, Cont<T0, T1, Remain...>, utility::when<(N == 1)>>
{
    using type = Cont<Processed..., T0, Value, Remain...>;
};


template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed, typename T0, typename T1, typename T2, typename ...Remain>
struct impl<Cont<Processed...>, N, Value, Cont<T0, T1, T2, Remain...>, utility::when<(N == 2)>>
{
    using type = Cont<Processed..., T0, T1, Value, Remain...>;
};


template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed, typename T0, typename T1, typename T2, typename T3, typename ...Remain>
struct impl<Cont<Processed...>, N, Value, Cont<T0, T1, T2, T3, Remain...>, utility::when<(N == 3)>>
{
    using type = Cont<Processed..., T0, T1, T2, Value, Remain...>;
};


template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed,
        typename T0, typename T1, typename T2, typename T3, typename ...Remain>
struct impl<Cont<Processed...>, N, Value, Cont<T0, T1, T2, T3, Remain...>, utility::when<(N >= 4 && N < 8)>>
{
    using type = impl<Cont<Processed..., T0, T1, T2, T3>, N - 4, Value, Cont<Remain...>>::type;
};

template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed,
        typename T0, typename T1, typename T2, typename T3,
        typename T4, typename T5, typename T6, typename T7,
        typename ...Remain>
struct impl<Cont<Processed...>, N, Value,
        Cont<T0, T1, T2, T3, T4, T5, T6, T7, Remain...>, utility::when<(N >= 8 && N < 16)>>
{
    using type = impl<Cont<Processed..., T0, T1, T2, T3, T4, T5, T6, T7>,
            N - 8, Value, Cont<Remain...>>::type;
};

template<template<typename...> typename Cont, int N, typename Value,
        typename...Processed,
        typename T0, typename T1, typename T2, typename T3,
        typename T4, typename T5, typename T6, typename T7,
        typename T8, typename T9, typename TA, typename TB,
        typename TC, typename TD, typename TE, typename TF,
        typename ...Remain>
struct impl<Cont<Processed...>, N, Value,
        Cont<T0, T1, T2, T3, T4, T5, T6, T7,
                T8, T9, TA, TB, TC, TD, TE, TF, Remain...>, utility::when<(N >= 16)>>
{
    using type = impl<Cont<Processed...,
            T0, T1, T2, T3, T4, T5, T6, T7,
            T8, T9, TA, TB, TC, TD, TE, TF>,
            N - 16, Value, Cont<Remain...>>::type;
};
}

template<typename Cont, int N, typename Value>
struct set;

template<template<typename...> typename Cont, int N, typename Value, typename ...Params>
requires (N < sizeof...(Params))
struct set<Cont<Params...>, N, Value>
{
    using type = typename NSSet::impl<Cont<>, N, Value, Cont<Params...>>::type;
};

template<typename Cont, int N, typename Value>
using set_t = set<Cont, N, Value>::type;

//fold
namespace NSFold {
template<typename Init, template<typename,typename> typename F, typename ...Remain>
struct impl
{
    using type = Init;
};
template<typename Init, template<typename,typename> typename F, typename T0>
struct impl<Init, F, T0>
{
    using type = F<Init, T0>;
};
template<typename Init, template<typename,typename> typename F, typename T0, typename T1>
struct impl<Init, F, T0, T1>
{
    using type = F<F<Init, T0>, T1>;
};
template<typename Init, template<typename,typename> typename F,
        typename T0, typename T1, typename T2>
struct impl<Init, F, T0, T1, T2>
{
    using type = F<F<F<Init, T0>, T1>, T2>;
};

template<typename Init, template<typename,typename> typename F,
        typename T0, typename T1, typename T2, typename T3>
struct impl<Init, F, T0, T1, T2, T3>
{
    using type = F<F<F<F<Init, T0>, T1>, T2>, T3>;
};
template<typename Init, template<typename,typename> typename F,
        typename T0, typename T1, typename T2, typename T3, typename T4>
struct impl<Init, F, T0, T1, T2, T3, T4>
{
    using type = F<F<F<F<F<Init, T0>, T1>, T2>, T3>, T4>;
};

template<typename Init, template<typename,typename> typename F,
        typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct impl<Init, F, T0, T1, T2, T3, T4, T5>
{
    using type = F<F<F<F<F<F<Init, T0>, T1>, T2>, T3>, T4>, T5>;
};
template<typename Init, template<typename,typename> typename F,
        typename T0, typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename ...Remain>
struct impl<Init, F, T0, T1, T2, T3, T4, T5, T6, Remain...>
{
    using type = impl<F<F<F<F<F<F<F<Init, T0>, T1>, T2>, T3>, T4>, T5>, T6>, F, Remain...>::type;
};
}
template<typename Init, typename Cont, template<typename,typename> typename F>
struct fold;
template<typename Init, template<typename...> typename Cont, typename...Params,
template<typename,typename > typename F>
struct fold<Init, Cont<Params...>, F>
{
    using type = NSFold::impl<Init, F, Params...>::type;
};

template<typename Init, typename InputCont, template<typename,typename> typename F>
using fold_t = fold<Init, InputCont, F>::type;

//transform
template<typename InCont, template<typename> typename F, template<typename...> typename OutCont>
struct transform;

template<template<typename...> typename InCont, typename ...Inputs,
template<typename> typename F, template<typename...> typename OutCont>
struct transform<InCont<Inputs...>, F, OutCont>
{
    using type = OutCont<typename F<Inputs>::type...>;
};

template<typename InCont, template<typename> typename F,
template<typename...> typename OutCont>
using transform_t = transform<InCont, F, OutCont>::type;

//cascade
template<typename Cont1, typename Cont2>
struct cascade;
template<template<typename...> typename Cont, typename...Params1, typename ...Params2>
struct cascade<Cont<Params1...>, Cont<Params2...>>
{
    using type = Cont<Params1..., Params2...>;
};

template<typename Cont1, typename Cont2>
using cascade_t = cascade<Cont1, Cont2>::type;

//push_back
template<typename Cont, typename ...Values>
struct push_back;
template<template<typename...> typename Cont, typename ...Params, typename ...Values>
struct push_back<Cont<Params...>, Values...>
{
    using type = Cont<Params..., Values...>;
};
template<typename Cont, typename ...Values>
using push_back_t = push_back<Cont, Values...>::type;

//size
template<typename Array>
struct size;
template<template<typename...> typename Array, typename ...Params>
struct size<Array<Params...>>
{
    static constexpr auto value = sizeof...(Params);
};

template<typename Array>
constexpr auto size_v = size<remove_const_ref_t<Array>>::value;

//head
template<typename Cont>
//requires (Cont::size > 0)
struct head;
template<template<typename...> typename Cont, typename Head, typename...Cases>
struct head<Cont<Head, Cases...>>
{
    using type = Head;
};

template<typename Cont>
using head_t = head<Cont>::type;

//tail
template<typename Cont>
struct tail;
template<template<typename...> typename Cont, typename Head, typename ...Cases>
struct tail<Cont<Head, Cases...>>
{
    using type = Cont<Cases...>;
};
template<typename Cont>
using tail_t = tail<Cont>::type;



}
METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_FACILITIES_SEQUENTIAL_HPP
