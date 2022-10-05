#pragma once

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {

template <class T>
class Vector {
 private:
  size_t _size;
  size_t _capacity;
  T *arr;

 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  // constructors
  Vector();
  explicit Vector(size_type n);
  explicit Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);

  // destructor
  ~Vector();

  // methods for accessing container elements
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  Vector<value_type> &operator=(Vector<value_type> &&v);
  Vector<value_type> &operator=(const Vector<T> &v);

  // methods for checking if a container is full
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // methods for dealing with the container iterator
  iterator begin();
  iterator end();

  // methods for changing the container
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  // bonus part
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);

  // additional
  T *doubleCapacity(size_type *capacity, size_type size);
};
}  // namespace s21

#include "s21_vector.inl"
