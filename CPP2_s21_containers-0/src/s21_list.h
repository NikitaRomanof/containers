#pragma once

#include <cmath>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class List {
 private:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

  /* --------------INNER CLASS Node-------------- */
  class Node {
   public:
    value_type _data;
    Node *_pNext;
    Node *_pPrev;
    Node(const_reference data = value_type(), Node *pNext = nullptr,
         Node *pPrev = nullptr)
        : _data(data), _pNext(pNext), _pPrev(pPrev) {}
  };

  /* --------------INNER CLASS ListIterator-------------- */
 public:
  class ListIterator {
   public:
    Node *_curIter;
    Node *_listHead;
    Node *_listTail;
    ListIterator();
    explicit ListIterator(const List<T> &other);
    ListIterator &operator++();
    ListIterator &operator--();
    reference operator*();
    bool operator!=(const ListIterator &other);
    bool operator==(const ListIterator &other);
  };

  /* --------------INNER CLASS ListConstIterator-------------- */
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    explicit ListConstIterator(const List<T> &other) : ListIterator(other) {}
    const_reference operator*() const;
    ListConstIterator &operator=(const ListIterator &other);
  };
  typedef ListIterator iterator;
  typedef ListConstIterator const_iterator;

  /* --------------LIST FIELDS-------------- */
 private:
  size_type _size;
  Node *_head;
  Node *_tail;

 public:
  /* --------------LIST FUNCTIONS-------------- */
  List();
  explicit List(size_type n);
  explicit List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();
  List<value_type> &operator=(List<value_type> &&l);
  List<value_type> &operator=(const List<T> &l);

  /* --------------LIST ELEMENT ACCESS-------------- */
  const_reference front();
  const_reference back();

  /* --------------LIST FUNC. ITERATORS-------------- */
  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();

  /* --------------LIST CAPACITY-------------- */
  bool empty();
  size_type size();
  size_type max_size();

  /* --------------LIST MODIFIERS-------------- */
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void clear();
  void swap(List &other);
  void erase(iterator pos);
  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, List &other);
  void merge(List &other);
  void sort();
  void reverse();
  void unique();

  /* --------------BONUS-------------- */
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);
  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
};

}  // namespace s21

#include "s21_list.inl"
