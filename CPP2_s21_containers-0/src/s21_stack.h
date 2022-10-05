#pragma once

#include <iostream>
#include "s21_node.h"
#include <limits>

namespace s21 {
template <class T>
class stack {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

 private:
    size_t _size;
    Node<T> *_head;

    void setRoot(Node<T> *element);
    void reverse();
    size_type max_size();

 public:
    stack();
    explicit stack(std::initializer_list<value_type> const &items);
    explicit stack(const stack &s);
    explicit stack(stack &&s);
    ~stack();

    const_reference top();
    bool empty();
    size_type size();
    void push(const_reference value);
    void pop();
    void swap(stack<T> &other);
    stack<value_type> &operator=(stack<T> &&s);
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  //  namespace s21

#include "s21_stack.inl"
