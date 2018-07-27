//
// Created by oleg on 27.07.18.
//

#pragma once
#include <memory>
#include <iostream>

template <class T, class U>
struct replace_allocator_arg { };

template<template<class> class Alloc, class U, class T>
struct replace_allocator_arg<Alloc<T>, U> {
    using type = Alloc<U>;
};

template <class T>
class node {
public:
    node(const T& el) noexcept :
            m_next(nullptr),
            m_data(el)
    { }

    void link_node(node<T>* n) noexcept {
        m_next = n;
    }

    node<T>* next() noexcept {
        return m_next;
    }

    const T& data() const noexcept {
        return m_data;
    }

private:
    node<T>*    m_next;
    T           m_data;
};

template <class T, class Alloc = std::allocator<T>>
class simple_list {
    using NodeAlloc = typename replace_allocator_arg<Alloc, node<T>>::type;

public:
    simple_list() noexcept :
            m_head(nullptr)
    { }

    ~simple_list() {
        clear();
    }

    void push(const T& el) {
        auto p = create_new_node(el);
        p->link_node(m_head);
        m_head = p;
    }

    void print_elements() noexcept {
        auto n = m_head;

        if (n)
            std::cout << n->data() << std::endl;

        while (n->next()) {
            n = n->next();
            std::cout << n->data() << std::endl;
        }
    }

    void clear() {
        while (delete_head());
    }

private:
    node<T>* create_new_node(const T& el) {
        auto p = std::allocator_traits<NodeAlloc>::allocate(m_node_alloc, 1);
        std::allocator_traits<NodeAlloc>::construct(m_node_alloc, p, el);
        return p;
    }

    bool delete_head() {
        if (m_head) {
            auto n = m_head;
            m_head = m_head->next();

            std::allocator_traits<NodeAlloc>::destroy(m_node_alloc, n);
            std::allocator_traits<NodeAlloc>::deallocate(m_node_alloc, n, 1);

            return true;
        }

        return false;
    }

private:
    node<T>*    m_head;
    NodeAlloc   m_node_alloc;
};
