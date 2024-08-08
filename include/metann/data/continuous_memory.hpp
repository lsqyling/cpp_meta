//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_DATA_CONTINUOUS_MEMORY_HPP
#define CPP_META_INCLUDE_METANN_DATA_CONTINUOUS_MEMORY_HPP
#include <cassert>
#include "allocator.hpp"
#include "metann/facilities/metann_trait.hpp"
METANN_NS_BEGIN
template<typename Elem, typename Device>
requires std::same_as<remove_const_ref_t<Elem>, Elem>
class continuous_memory
{
    using elem_type = Elem;

public:
    explicit continuous_memory(size_t psize)
    : m_mem(allocator<Device>::template allocate<elem_type>(psize)), m_size(psize) {}

    continuous_memory shift(size_t pos) const
    {
        assert(pos < m_size);
        return continuous_memory(std::shared_ptr<elem_type >(m_mem.get() + pos), m_size - pos);
    }

    auto raw_memory() const
    {
        return m_mem.get();
    }

    bool is_shared() const
    {
        return m_mem.use_count() > 1;
    }

    size_t size() const
    {
        return m_size;
    }

    bool operator==(const continuous_memory &val) const noexcept
    {
        return (m_mem == val.m_mem) && (m_size == val.m_size);
    }

    bool operator!=(const continuous_memory &val) const noexcept
    {
        return !operator==(val);
    }


private:
    continuous_memory(std::shared_ptr<elem_type> ptr, size_t psize)
    : m_mem(std::move(ptr)), m_size(psize) {}

    std::shared_ptr<elem_type > m_mem;
    size_t m_size;
};



METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_DATA_CONTINUOUS_MEMORY_HPP
