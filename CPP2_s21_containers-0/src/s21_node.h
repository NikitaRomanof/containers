#pragma once

namespace s21 {
template <class T>
class Node {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

 private:
    T _data;
    Node<T> *_pastElement;

 public:
    explicit Node(const_reference value);
    ~Node();
    const_reference getData();
    void setPastElement(Node *element);
    Node* getPastElement();
};
}  //  namespace s21

#include "s21_node.inl"
