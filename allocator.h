//
// Created by oleg on 26.07.18.
//

#pragma once

#include <new>
#include <iostream>

template <class T>
class resize_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

public:
    resize_allocator()
            : m_pool(nullptr), m_pool_size(0), m_allocated(0) { }

    pointer allocate(size_type n, size_type chunk_size = 10) {
        if (!m_pool) {
            reserve(chunk_size);
        }
        if (m_allocated < m_pool_size) {
            return m_pool + m_allocated++;
        }

        throw std::bad_alloc();
    }

    void deallocate(pointer p, size_type n) {
        if (m_pool) {
            ::operator delete(m_pool);
            m_pool = nullptr;
        }
    }

    template <class U, class... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

private:
    void reserve(size_type n) {
        m_pool = reinterpret_cast<pointer>(::operator new(n * sizeof(T)));
        m_pool_size = n;
        m_allocated = 0;
    }

private:
    pointer     m_pool;
    size_type   m_pool_size;
    size_type   m_allocated;
};
