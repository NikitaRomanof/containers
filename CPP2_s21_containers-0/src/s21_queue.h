#pragma once

#include <iostream>
#include "s21_node.h"
#include <limits>

namespace s21 {
template <class T>
class queue {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

 private:
    size_t _size;
    Node<T> *_head;
    Node<T> *_tail;

    void setRoot(Node<T> *element);
    void setTail(Node<T> *element);
    void reverse();
    size_type max_size();

 public:
    queue();
    explicit queue(std::initializer_list<value_type> const &items);
    explicit queue(const queue &s);
    explicit queue(queue &&s);
    ~queue();

    const_reference front();
    const_reference back();
    bool empty();
    size_type size();
    void push(const_reference value);
    void pop();
    void swap(queue<T> &other);
    queue<value_type> &operator=(queue<T> &&s);
    template <typename... Args>
    void emplace_back(Args&&... args);
};
}  //  namespace s21

#include "s21_queue.inl"
