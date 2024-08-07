//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_DATA_ALLOCATOR_HPP
#define CPP_META_INCLUDE_METANN_DATA_ALLOCATOR_HPP
#include <mutex>
#include <unordered_map>
#include <deque>
#include "device_tag.hpp"

METANN_NS_BEGIN
template<typename Device>
struct allocator;

template<>
struct allocator<device_tags::cpu>
{
private:
    struct alloc_helper
    {
        std::unordered_map<size_t, std::deque<void *>> m_buf;
        ~alloc_helper()
        {
            for (auto &p: m_buf)
            {
                auto &ref = p.second;
                for (auto &ptr: ref)
                {
                    char *buf = static_cast<char*>(ptr);
                    delete[] buf;
                }
            }
        }
    };

    struct desimpl
    {
        explicit desimpl(std::deque<void *> &pbuf) : m_refpool(pbuf) {}
        void operator()(void *p_val)
        {
            std::lock_guard lock(m_mut);
            m_refpool.push_back(p_val);
        }
    private:
        std::deque<void *> &m_refpool;
    };

public:
    template<typename T>
    static std::shared_ptr<T> allocate(size_t elemsize)
    {
        if (elemsize == 0)
            return nullptr;
        elemsize *= sizeof(T);
//        adjust the elemsize is nK
        if (elemsize & 0x3ff)
            elemsize = ((elemsize >> 10) + 1) << 10;

        std::lock_guard lock(m_mut);
        static alloc_helper aux;
        auto &slot = aux.m_buf[elemsize];
        if (slot.empty())
        {
            auto raw_buf = reinterpret_cast<T*>(new char[elemsize]);
            return std::shared_ptr<T>(raw_buf, desimpl(slot));
        }
        else
        {
            auto mem = reinterpret_cast<T*>(slot.back());
            slot.pop_back();
            return std::shared_ptr<T>(mem, desimpl(slot));
        }
    }


private:
    inline static std::mutex m_mut;
};





METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_DATA_ALLOCATOR_HPP
