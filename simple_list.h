//
// Created by oleg on 27.07.18.
//

#pragma once
#include <memory>

template <class T, class U>
struct replace_allocator_arg { };

template<template<class> class Alloc, class U, class T>
struct replace_allocator_arg<Alloc<T>, U>
{
    using type = Alloc<U>;
};

template <class T>
class node {
public:
    node() { }


private:
    node* m_next;
    T m_data;
};

template <class T, class Alloc = std::allocator<T>>
class simple_list {
    using NodeAlloc = typename replace_allocator_arg<Alloc, node<T>>::type;

public:
    simple_list(const Alloc& alloc = Alloc())
            : m_head(nullptr),
            m_alloc(alloc)
    { }

    ~simple_list() {

    }

    void push(const T& el) {
        auto p = std::allocator_traits<Alloc>::allocate(m_alloc, 1);
        std::allocator_traits<Alloc>::construct(m_alloc, p, el);
    }

private:
    node<T>* m_head;
    NodeAlloc m_alloc;
};
