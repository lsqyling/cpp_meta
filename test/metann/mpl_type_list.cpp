//
// Created by 10580.
//
#include "metann/facilities/type_list.hpp"


using namespace metann;

template<typename ...T>
struct predicate
{
    static constexpr bool value = ((sizeof(T) == 4) && ...);
};

using list = type_list<char, int, long, float, double>;
using empty = type_list<>;

void test_aux()
{
    static_assert(is_less<3, 4>);
    static_assert(negate<predicate>::type<char, int, long, float, double>::value);
    static_assert(is_not_same<char, int>::value);
    info(is_less);
    info(negate);
    info(is_not_same);
    std::cout << "------------------\n";
}

template<typename ...Ts>
struct cont;

void test_type_list()
{
    static_assert(std::same_as<type_list_from_t<cont<char, int, float>>, type_list<char, int, float>>);
    static_assert(std::same_as<type_list_from_t<cont<>>, type_list<>>);
    info(type_list_from);

    using t0 = type_list<char, int>;
    using t1 = t0::append<long, float, double>;
    using t2 = t0::prepend<long, float, double>;
    static_assert(std::same_as<t1, type_list<char,int,long,float,double>>);
    static_assert(std::same_as<t2, type_list<long,float, double,char,int>>);
    info(append);
    info(prepend);
    using t3 = t0::to<predicate>;
    static_assert(std::same_as<t3, predicate<char, int>>);
    info(to);

    static_assert(std::same_as<head_t<t0>, char>);
    static_assert(std::same_as<tail_t<t0>, type_list<int>>);
    static_assert(std::same_as<last_t<t0>, int>);
    info(head);
    info(tail);
    info(last);

    using t4 = drop_last_t<list>;
    static_assert(std::same_as<t4, type_list<char,int,long,float>>);
    info(drop);
    std::cout << "------------------\n";
}

template<size_t I>
struct type_value
{
    using type = type_value;
    static constexpr size_t value = I;
};

template<size_t I>
using v = type_value<I>;

template<typename T>
struct double_
{
    using type = type_value<2*T::value>;
};

template<typename T>
struct odd
{
    using type = T;
    static constexpr bool value = T::value % 2 == 1;
};

template<typename U, typename T>
struct add
{
    using type = v<U::value + T::value>;
};

template<typename T>
struct bigger_eq
{
    static constexpr bool value = sizeof(T) >= 8;
};

template<typename T>
struct less_4
{
    static constexpr bool value = sizeof(T) < 4;
};



void test_alg5()
{
    using t0 = type_list<char,int,float,char,double,char,long>;
    using t1 = split_if_t<t0, less_4>;
    static_assert(std::same_as<t1, type_list<type_list<int,float>,type_list<double>, type_list<long>>>);

    using t2 = split_t<t0, char>;
    static_assert(std::same_as<t2, type_list<type_list<int,float>,type_list<double>, type_list<long>>>);
    info(split_if);
    info(split);

    static_assert(std::same_as<reverse_sequence_t<std::integer_sequence<unsigned,0,1,2,3,4,5>>,
            std::integer_sequence<unsigned,5,4,3,2,1,0>>);
    info(reverse_sequence);

    static_assert(tuple_size_v<t0> == 7);
    static_assert(std::same_as<tuple_element_t<4,t0>, double>);
    static_assert(std::same_as<tuple_element_t<0,t0>, char>);
    static_assert(std::same_as<tuple_element_t<1,t0>, int>);
    info(tuple_size);
    info(tuple_element);

    std::cout << "------------------\n";
}



void test_alg4()
{
    struct node0;
    struct node1;
    struct node2;
    struct node3;
    struct node4;
    struct node5;
    struct node6;

    using t0 = type_list<char,int,long,float,double, node0,node1,node2,node3>;
    using t1 = type_list<char,float,double,node4,node5,node6>;

    using t4 = union_set_t<t0, t1>;
    using t5 = intersection_set_t<t0, t1>;
    using t6 = difference_set_t<t0, t1>;
    using t7 = symmetric_difference_set_t<t0, t1>;

    static_assert(std::same_as<t4,
            type_list<char,int,long,float,double,node0,node1,node2,node3,node4,node5,node6>>);
    static_assert(std::same_as<t5,
            type_list<char,float,double>>);
    static_assert(std::same_as<t6,
            type_list<int,long,node0,node1,node2,node3>>);
    static_assert(std::same_as<t7,
            type_list<int,long,node0,node1,node2,node3,node4,node5,node6>>);

    info(union_set);
    info(intersection_set);
    info(difference_set);
    info(symmetric_difference_set);

    std::cout << "------------------\n";
}



void test_alg3()
{
    using t0 = type_list<char,int,long,float,double>;
    using t1 = reverse_t<t0>;
    static_assert(std::same_as<t1, type_list<double,float,long,int,char>>);
    info(reverse);

    using t2 = type_list<char,char,char,int,int,int,int>;
    static_assert(count_v<t2, char> == 3);
    static_assert(count_v<t2, int> == 4);
    static_assert(count_v<t2, long> == 0);
    info(count);

    static_assert(std::same_as<at_t<t0, 2>, long>);
    static_assert(std::same_as<at_t<t0, 3>, float>);
    static_assert(std::same_as<at_t<t0, 4>, double>);
    info(at);

    using t3 = first_nt<t0, 3>;
    static_assert(std::same_as<t3, type_list<char,int,long>>);
    info(fist);

    struct node;
    using t4 = replace_t<t0, double, node>;
    static_assert(std::same_as<t4, type_list<char,int,long,float,node>>);
    info(replace);


    std::cout << "------------------\n";
}




void test_alg2()
{
    using t0 = type_list<char,int,long,float,double>;
    static_assert(find_t<t0, char>::value == 0);
    static_assert(find_v<t0, char> == 0);
    static_assert(find_v<t0, int> == 1);
    static_assert(find_v<t0, long> == 2);
    static_assert(find_v<t0, float> == 3);
    static_assert(find_v<t0, double> == 4);
    static_assert(find_v<t0, short> == npos);
    info(find);
    static_assert(find_if_t<t0, bigger_eq>::value == 4);
    static_assert(find_if_v<t0, bigger_eq> == 4);
    info(find_if);

    using t1 = type_list<char,char,int,int,long,long,float,float,double,double>;
    using t2 = unique_t<t1>;
    static_assert(std::same_as<t2, t0>);
    info(unique);


    std::cout << "------------------\n";
}



void test_alg1()
{
    using t0 = type_list<char,int>;
    using t1 = type_list<long>;
    using t2 = type_list<float,double>;

    using t3 = concat_t<t0>;
    using t4 = concat_t<t0, t1, t2>;
    static_assert(std::same_as<t3, t0>);
    static_assert(std::same_as<t4, list>);
    info(concat);
    static_assert(contain_v<t4, double>);
    info(contain);
    std::cout << npos << std::endl;

    std::cout << "------------------\n";
}


void test_alg()
{
    using t0 = type_list<v<0>, v<1>, v<2>, v<3>, v<4>, v<5>>;
    using t1 = map_t<t0, double_>;
    static_assert(std::same_as<t1, type_list<v<0>, v<2>, v<4>, v<6>, v<8>, v<10>>>);
    info(map);
    using t2 = filter_t<t0, odd>;
    static_assert(std::same_as<t2, type_list<v<1>, v<3>, v<5>>>);
    info(filter);

    using t3 = type_list<char,int,float,double>;
    using t4 = remove_t<t3, char>;
    static_assert(std::same_as<t4, type_list<int,float,double>>);
    using t5 = remove_t<t3, float>;
    static_assert(std::same_as<t5, type_list<char,int,double>>);
    info(remove);

    using t6 = remove_if_t<t0, odd>;
    static_assert(std::same_as<t6, type_list<v<0>,v<2>,v<4>>>);
    info(remove_if);

    using t7 = fold_t<t0, v<100>, add>;
    static_assert(t7::value == 115);
    info(fold);
    std::cout << "------------------\n";
}

namespace analyze_at {

template<typename T>
T index_at(T *arr, size_t idx)
{
    if (idx == 0)
        return arr[0];

    return index_at(arr+1, idx-1);
}

void test_index_at()
{
    int array[10] = {0,1,2,3,4,5,6,7,8,9};
    std::cout << index_at(array, 8) << std::endl;
    info(index_at);
    std::cout << "------------------\n";
}

void test_decay()
{
    static_assert(std::is_same_v<std::decay_t<const int>, int>);
    static_assert(std::is_same_v<std::decay_t<const int&>, int>);
    static_assert(std::is_same_v<std::decay_t<const int*>, const int*>);
    static_assert(std::is_same_v<std::decay_t<int*const>, int*>);
    static_assert(std::is_same_v<std::decay_t<const volatile int>, int>);
    static_assert(std::is_same_v<std::decay_t<const volatile int&>, int>);
    static_assert(std::is_same_v<std::decay_t<const volatile int*>, const volatile int*>);
    static_assert(std::is_same_v<std::decay_t<const volatile int*const volatile&>, const volatile int*>);
    static_assert(std::is_same_v<std::decay_t<const int[3]>, const int*>);
    static_assert(std::is_same_v<std::decay_t<int(&)[3]>, int*>);
    info(decay);
    std::cout << "------------------\n";
}

template<int a, int b> //better
constexpr int add = a + b;

template<int a, int b>
constexpr int add_() //bad
{
    return a + b;
}


void test_meta_add()
{
    static_assert(add<3, 4> == 7);
    static_assert(add_<3, 4>() == 7);
    info(add);

    std::cout << "------------------\n";
}
}







int main(int argc, char *argv[])
{
    test_aux();
    test_type_list();
    test_alg();
    test_alg1();
    test_alg2();
    test_alg3();
    test_alg4();
    test_alg5();
    analyze_at::test_index_at();
    analyze_at::test_decay();
    analyze_at::test_meta_add();

    return 0;
}


















