//
// Created by 10580.
//
#include <concepts>
#include <type_traits>
#include <iostream>
#include <vector>
#include "metann/data/category_tags.hpp"
#include "metann/data/traits.hpp"

struct intref
{
    explicit intref(int &x) : m_i(x) {}
    void operator()(void *ptr) const
    {
        m_i = *static_cast<int*>(ptr);
        ++m_i;
        std::cout << __func__ << ": ++m_i = " << m_i << std::endl;
    }
private:
    int &m_i;
};


void test_intref()
{
    int x = 3;
    intref xi(x);

    intref i(std::move(xi));
    i(&x);

    static_assert(!std::is_default_constructible_v<intref>);

    static_assert(std::is_copy_constructible_v<intref>);
    static_assert(std::is_move_constructible_v<intref>);

    static_assert(!std::is_copy_assignable_v<intref>);
    static_assert(!std::is_move_assignable_v<intref>);

    static_assert(std::is_destructible_v<intref>);
}

struct vector_ref
{
    explicit vector_ref(std::vector<int> &vi) : m_vi(vi) {}
private:
    std::vector<int> &m_vi;
};

void test_vector_ref()
{
    std::vector<int> vi{0, 1, 2, 3, 4, 5};
    vector_ref vr(vi);
    vector_ref vc(vr);
    vector_ref vm(std::move(vc));

    static_assert(!std::is_default_constructible_v<vector_ref>);

    static_assert(std::is_copy_constructible_v<vector_ref>);
    static_assert(std::is_move_constructible_v<vector_ref>);

    static_assert(!std::is_copy_assignable_v<vector_ref>);
    static_assert(!std::is_move_assignable_v<vector_ref>);

    static_assert(std::is_destructible_v<vector_ref>);
}








int main(int argc, char* argv[])
{
    test_intref();
    test_vector_ref();

    return 0;
}




