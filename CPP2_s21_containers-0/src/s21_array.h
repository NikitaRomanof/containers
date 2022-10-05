#pragma once

#include <iostream>
#include <limits>

namespace s21 {
template <class T, size_t L>
class array {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

 private:
    value_type _array[L]{0};
    size_type _size;

 public:
    array();
    explicit array(std::initializer_list<value_type> const &items);
    explicit array(const array &a);
    explicit array(array &&a);
    ~array();

    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    iterator data();

    iterator begin();
    iterator end();

    bool empty();
    size_type size();
    size_type max_size();

    void swap(array& other);
    void fill(const_reference value);

    array<value_type, L> &operator=(array &&s);
};
}  //  namespace s21

#include "s21_array.inl"
