#pragma once

#include <bits/stl_tree.h>

#include <iostream>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

namespace s21 {

template <class T>
class tree {
 public:
  using value_type = T;
  using node_type = tree<T>;

  tree(T k = T(), node_type *p = nullptr, node_type *l = nullptr,
       node_type *r = nullptr)
      : _key(k), _parent(p), _left(l), _right(r) {}
  ~tree() {
    _parent = nullptr;
    _left = nullptr;
    _right = nullptr;
  }

  value_type &getKey() { return _key; }
  node_type *getParent() { return _parent; }
  node_type *getLeft() { return _left; }
  node_type *getRight() { return _right; }

  // void setKey(T k = T()) { _key = k; }
  void setParent(node_type *p = nullptr) { _parent = p; }
  void setLeft(node_type *p = nullptr) { _left = p; }
  void setRight(node_type *p = nullptr) { _right = p; }

 private:
  T _key;
  node_type *_parent;
  node_type *_left;
  node_type *_right;
};

template <class T>
class set {
 public:
  class set_iter;
  // Member type
  using value_type = T;
  using const_value_type = const T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = set_iter;
  using const_iterator = const set_iter;
  using size_type = size_t;
  using node_type = tree<T>;
  using pair_type = std::pair<iterator, bool>;

  // Member functions
  set();
  explicit set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(set &&s);

  // Iterators
  class set_iter {
   public:
    node_type *_pos;

    set_iter();
    ~set_iter() {}
    void operator=(const_iterator &i);
    const_reference operator*();
    void operator--();
    void operator++();
    bool operator==(const_iterator &i);
    bool operator!=(const_iterator &i);
  };

  iterator begin();
  iterator end();

  // Set Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  pair_type insert(const_reference value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  // Lookup
  iterator find(const_reference key);
  bool contains(const_reference key);

  // Bonus
  template <class... Args>
  pair_type emplace(Args &&...args);

  // support
  void s21_set_isfull(size_t num);
  void s21_print_set();
  void s21_print_tree(node_type *tree);

 private:
  // Tree
  node_type *_root;
  size_type _size;

  void s21_tree_copy(node_type *tree, set *set_new);
  void s21_tree_del(node_type **tree);
  void s21_tree_erase(node_type *tree);
  node_type *s21_tree_begin();
  node_type *s21_tree_end();
  node_type *s21_tree_prev(node_type *tree, const_value_type &key,
                           value_type *min_prev_key);
  node_type *s21_tree_next(node_type *tree, const_value_type &key,
                           value_type *min_next_key);
  node_type *s21_tree_find(node_type *tree, const_value_type &key);
  bool s21_tree_contains(node_type *tree, const_value_type &key);
  pair_type s21_tree_insert(node_type *tree, const_value_type &key);
  void s21_tree_clear_merge(set *tree, set *tree_success);
};
}  // namespace s21

#include "s21_set.inl"
