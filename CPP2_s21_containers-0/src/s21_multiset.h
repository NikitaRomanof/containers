#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <class Key>
class multiset {
 public:
  enum COLOR { RED, BLACK, BLUE, GREEN, WHITE };
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // Nodes class and functions
 private:
  class Node {
   public:
    Key val;
    COLOR color;
    COLOR color2;
    Node *left, *right, *parent, *similar;
    explicit Node(Key val)
        : val(val),
          color(RED),
          color2(WHITE),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          similar(nullptr) {}
    Node *uncle();
    bool isOnLeft();
    Node *sibling();
    void moveDown(Node *nParent);
    bool hasRedChild();
  };
  Node *root;
  size_type ms_size;

  // Iterator
 public:
  class MultisetIterator {
   public:
    Node *current;
    Node *previous;
    MultisetIterator() : current(nullptr), previous(nullptr) {}
    explicit MultisetIterator(Node *some_node) {
      current = some_node;
      previous = current->parent;
    }
    const Key &operator*();
    void operator++();
    void operator--();
    bool operator==(MultisetIterator other);
    bool operator!=(MultisetIterator other);
  };

  class MultisetConstIterator : MultisetIterator {
   public:
    MultisetConstIterator() : MultisetIterator() {}
    explicit MultisetConstIterator(Node *some_node)
        : MultisetIterator(some_node) {
      this->current = some_node;
      this->previous = this->current->parent;
    }
    const Key &operator*() {
      if (this->current == nullptr) {
        throw std::invalid_argument("Cannot dereference null pointer");
      }
      return this->current->val;
    }
    bool operator!=(MultisetIterator other);
  };

  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;
  using iter_pair = std::pair<iterator, iterator>;

 public:
  // constructors
  multiset() : root(nullptr), ms_size(0) {}
  explicit multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &ms);  // copy constructor
  multiset(multiset &&ms);       // move constructor
  ~multiset();

  // Tree Manipulating functions
  void leftRotate(Node *x);
  void rightRotate(Node *x);
  void swapColors(Node *x1, Node *x2);
  void swapValues(Node *u, Node *v);
  void fixRedRed(Node *x);
  Node *successor(Node *x);
  Node *BSTreplace(Node *x);
  void deleteNode(Node *v);
  void fixDoubleBlack(Node *x);
  void inorder(Node *x);

  Node *getRoot();
  void setRoot(Node *new_root);
  Node *search(Key n);
  void deleteByVal(Key n);

  void printInOrder();

 public:
  multiset<Key> &operator=(multiset &&ms);

  // Multiset Iterators
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  // // Multiset Capacity
  size_type size();      // returns the number of elements
  bool empty();          // checks whether the container is empty
  size_type max_size();  // returns the maximum possible number of elements

  // Multiset Modifiers
  void clear();  // clears the contents
  iterator insert(const value_type &value);
  void erase(iterator pos);     // erases element at pos
  void swap(multiset &other);   // swaps the contents
  void merge(multiset &other);  // splices nodes from another container

  // Multiset Lookup
  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  iter_pair equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  // additional tools
  Node *findMin();
  Node *findMax();
  void recursiveClear(Node *&node);
  void recursiveCopy(const Node *node);
};

}  // namespace s21

#include "s21_multiset.inl"
