namespace s21 {

template <class Key>
typename multiset<Key>::Node *multiset<Key>::Node::uncle() {
  if (parent == nullptr || parent->parent == nullptr) return nullptr;
  if (parent->isOnLeft())
    return parent->parent->right;
  else
    return parent->parent->left;
}

template <class Key>
bool multiset<Key>::Node::isOnLeft() {
  return this == parent->left;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::Node::sibling() {
  if (parent == nullptr) return nullptr;
  if (isOnLeft()) return parent->right;
  return parent->left;
}

template <class Key>
void multiset<Key>::Node::moveDown(Node *nParent) {
  if (parent != nullptr) {
    if (isOnLeft()) {
      parent->left = nParent;
    } else {
      parent->right = nParent;
    }
  }
  nParent->parent = parent;
  parent = nParent;
}

template <class Key>
bool multiset<Key>::Node::hasRedChild() {
  return (left != nullptr && left->color == RED) ||
         (right != nullptr && right->color == RED);
}

template <class Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : root(nullptr), ms_size(0) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    insert(*it);
    ++ms_size;
  }
}

template <class Key>
multiset<Key>::multiset(const multiset &ms) : root(nullptr), ms_size(0) {
  recursiveCopy(ms.root);
  ms_size = ms.ms_size;
}

template <class Key>
multiset<Key>::multiset(multiset &&ms) : root(nullptr), ms_size(0UL) {
  *this = std::move(ms);
}

template <class Key>
multiset<Key>::~multiset() {
  clear();
}

template <class Key>
multiset<Key> &multiset<Key>::operator=(multiset &&ms) {
  if (this->root == ms.root) {
    throw std::invalid_argument("Cannot move object into itself");
  }
  if (root) this->clear();
  std::swap(root, ms.root);
  std::swap(ms_size, ms.ms_size);
  return *this;
}

template <class Key>
void multiset<Key>::leftRotate(Node *x) {
  if (x->right != nullptr) {
    Node *nParent = x->right;
    if (x == root) root = nParent;
    x->moveDown(nParent);
    x->right = nParent->left;
    if (nParent->left != nullptr) nParent->left->parent = x;
    nParent->left = x;
  }
}

template <class Key>
void multiset<Key>::rightRotate(Node *x) {
  if (x->left != nullptr) {
    Node *nParent = x->left;
    if (x == root) root = nParent;
    x->moveDown(nParent);
    x->left = nParent->right;
    if (nParent->right != nullptr) nParent->right->parent = x;
    nParent->right = x;
  }
}

template <class Key>
void multiset<Key>::swapColors(Node *x1, Node *x2) {
  COLOR temp;
  temp = x1->color;
  x1->color = x2->color;
  x2->color = temp;
}

template <class Key>
void multiset<Key>::swapValues(Node *u, Node *v) {
  int temp;
  temp = u->val;
  u->val = v->val;
  v->val = temp;
}

template <class Key>
void multiset<Key>::fixRedRed(Node *x) {
  if (x == root) {
    x->color = BLACK;
    return;
  }
  Node *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
  if (parent->color != BLACK) {
    if (uncle != nullptr && uncle->color == RED) {
      parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      fixRedRed(grandparent);
    } else {
      if (parent->isOnLeft()) {
        if (x->isOnLeft()) {
          swapColors(parent, grandparent);
        } else {
          leftRotate(parent);
          swapColors(x, grandparent);
        }
        rightRotate(grandparent);
      } else {
        if (x->isOnLeft()) {
          rightRotate(parent);
          swapColors(x, grandparent);
        } else {
          swapColors(parent, grandparent);
        }
        leftRotate(grandparent);
      }
    }
  }
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::successor(Node *x) {
  Node *temp = x;
  while (temp->left != nullptr) temp = temp->left;
  return temp;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::BSTreplace(Node *x) {
  if (x->left != nullptr && x->right != nullptr) return successor(x->right);
  if (x->left == nullptr && x->right == nullptr) return nullptr;
  if (x->left != nullptr)
    return x->left;
  else
    return x->right;
}

template <class Key>
void multiset<Key>::deleteNode(Node *v) {
  Node *u = BSTreplace(v);
  if (v->color2 == GREEN || v->color2 == BLUE) {
    while (v->similar != nullptr) {
      v = v->similar;
    }
    if (v->parent->color2 == BLUE) v->parent->color = WHITE;
    v->parent->similar = nullptr;
    delete v;
    return;
  }
  bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
  Node *parent = v->parent;
  if (u == nullptr) {
    if (v == root) {
      root = nullptr;
    } else {
      if (uvBlack) {
        fixDoubleBlack(v);
      } else {
        if (v->sibling() != nullptr) v->sibling()->color = RED;
      }
      if (v->isOnLeft()) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    }
    delete v;
    return;
  }
  if (v->left == nullptr || v->right == nullptr) {
    if (v == root) {
      v->val = u->val;
      v->left = v->right = nullptr;
      delete u;
    } else {
      if (v->isOnLeft()) {
        parent->left = u;
      } else {
        parent->right = u;
      }
      delete v;
      u->parent = parent;
      if (uvBlack) {
        fixDoubleBlack(u);
      } else {
        u->color = BLACK;
      }
    }
    return;
  }
  swapValues(u, v);
  deleteNode(u);
}

template <class Key>
void multiset<Key>::fixDoubleBlack(Node *x) {
  if (x == root) return;
  Node *sibling = x->sibling(), *parent = x->parent;
  if (sibling == nullptr) {
    fixDoubleBlack(parent);
  } else {
    if (sibling->color == RED) {
      parent->color = RED;
      sibling->color = BLACK;
      if (sibling->isOnLeft()) {
        rightRotate(parent);
      } else {
        leftRotate(parent);
      }
      fixDoubleBlack(x);
    } else {
      if (sibling->hasRedChild()) {
        if (sibling->left != nullptr && sibling->left->color == RED) {
          if (sibling->isOnLeft()) {
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rightRotate(parent);
          } else {
            sibling->left->color = parent->color;
            rightRotate(sibling);
            leftRotate(parent);
          }
        } else {
          if (sibling->isOnLeft()) {
            sibling->right->color = parent->color;
            leftRotate(sibling);
            rightRotate(parent);
          } else {
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            leftRotate(parent);
          }
        }
        parent->color = BLACK;
      } else {
        sibling->color = RED;
        if (parent->color == BLACK)
          fixDoubleBlack(parent);
        else
          parent->color = BLACK;
      }
    }
  }
}

#ifdef GCOV
template <class Key>
void multiset<Key>::inorder(Node *x) {
  if (x == nullptr) return;
  inorder(x->left);
  std::cout << x->val << " ";
  inorder(x->right);
}
#endif

template <class Key>
typename s21::multiset<Key>::iterator multiset<Key>::insert(
    const value_type &value) {
  if (ms_size >= max_size()) {
    throw std::out_of_range("Not enough memory to append element");
  }
  Node *newNode = new Node(value);
  if (root == nullptr) {
    newNode->color = BLACK;
    root = newNode;
  } else {
    Node *temp = search(value);
    newNode->parent = temp;
    if (value < temp->val) {
      temp->left = newNode;
    } else if (value == temp->val) {
      newNode->color2 = GREEN;
      temp->color2 = BLUE;
      while (temp->similar != nullptr) temp = temp->similar;
      temp->similar = newNode;
      newNode->parent = temp;
    } else {
      temp->right = newNode;
    }
    if (newNode->color2 == WHITE) fixRedRed(newNode);
  }
  iterator it(newNode);
  return it;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::search(Key n) {
  Node *temp = root;
  while (temp != nullptr) {
    if (n <= temp->val) {
      if (temp->left == nullptr) {
        break;
      } else if (n == temp->val) {
        break;
      } else {
        temp = temp->left;
      }
    } else {
      if (temp->right == nullptr)
        break;
      else
        temp = temp->right;
    }
  }
  return temp;
}

// Iterator functions
template <class Key>
const Key &multiset<Key>::iterator::operator*() {
  if (current == nullptr) {
    std::invalid_argument("Cannot deeference null pointer");
  }
  return current->val;
}

template <class Key>
bool multiset<Key>::iterator::operator==(MultisetIterator other) {
  return this->current == other.current;
}

template <class Key>
bool multiset<Key>::iterator::operator!=(MultisetIterator other) {
  return !operator==(other);
}

template <class Key>
void multiset<Key>::iterator::operator++() {
  if (current == nullptr && previous == nullptr) {
    throw std::invalid_argument("Cannot increase empty iterator");
  }
  if (current != nullptr) {
    if (current->color2 == BLUE) {
      while (current->similar != nullptr) {
        current = current->similar;
      }
      previous = current->parent;
    } else if (current->color2 == GREEN) {
      previous = current;
      current = current->parent;
      if (current->color2 == BLUE) {
        if (current->right != nullptr) {
          current = current->right;
          while (current->left != nullptr) current = current->left;
          previous = current->parent;
        } else if (current->parent != nullptr) {
          previous = current;
          current = current->parent;
        }
      }
    } else {
      if (current->parent != nullptr) {
        if (current->right == nullptr && current->isOnLeft()) {
          previous = current->parent;
          current = current->parent;
        } else if (current->right != nullptr) {
          current = current->right;
          while (current->left != nullptr) current = current->left;
          previous = current->parent;
        } else {
          previous = current;
          while (current->parent != nullptr && !current->isOnLeft()) {
            current = current->parent;
          }
          if (current->parent == nullptr) {
            previous = current;
            current = nullptr;
          } else {
            previous = current;
            current = current->parent;
          }
        }
      } else {
        if (current->right != nullptr) {
          current = current->right;
          while (current->left != nullptr) current = current->left;
          previous = current->parent;
        }
      }
    }
  } else {
    current = previous;
    previous = nullptr;
  }
}

template <class Key>
void multiset<Key>::iterator::operator--() {
  if (current == nullptr && previous == nullptr) {
    throw std::invalid_argument("Cannot decrease empty iterator");
  }
  if (current != nullptr) {
    if (current->color2 == BLUE) {
      while (current->similar != nullptr) {
        current = current->similar;
      }
      previous = current->parent;
    } else if (current->color2 == GREEN) {
      previous = current;
      current = current->parent;
      if (current->color2 == BLUE) {
        if (current->left != nullptr) {
          current = current->left;
          while (current->right != nullptr) current = current->right;
          previous = current->parent;
        } else if (current->parent != nullptr) {
          if (!current->isOnLeft()) {
            previous = current;
            current = current->parent;
          } else {
            while (current->parent != nullptr && current->isOnLeft())
              current = current->parent;
            previous = current;
            current = current->parent;
          }
        }
      }
    } else {
      if (current->parent != nullptr) {
        if (!current->isOnLeft() && current->left == nullptr) {
          previous = current->parent;
          current = current->parent;
        } else if (current->left != nullptr) {
          current = current->left;
          while (current->right != nullptr) current = current->right;
          previous = current->parent;
        } else {
          previous = current;
          while (current->parent != nullptr && current->isOnLeft())
            current = current->parent;
          if (current->parent != nullptr) {
            current = current->parent;
          } else {
            current = nullptr;
            previous = previous->right;
          }
        }
      } else {
        if (current->left != nullptr) {
          current = current->left;
          while (current->right != nullptr) current = current->right;
          previous = current->parent;
        }
      }
    }
  } else {
    current = previous;
    previous = nullptr;
  }
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::getRoot() {
  return root;
}

// Multiset Iterators
template <class Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  iterator iter;
  iter.current = this->findMin();
  return iter;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  iterator iter;
  iter.previous = this->findMax();
  iter.current = nullptr;
  return iter;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::findMin() {
  Node *current = root;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <class Key>
typename multiset<Key>::Node *multiset<Key>::findMax() {
  Node *current = root;
  while (current->right != nullptr) {
    current = current->right;
  }
  return current;
}

template <class Key>
bool multiset<Key>::empty() {
  return (root == nullptr && ms_size == 0);
}

template <class Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return ms_size;
}

template <class Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return SIZE_MAX / sizeof(Node);
}

template <class Key>
void multiset<Key>::clear() {
  if (root != nullptr) {
    recursiveClear(root);
  }
  ms_size = 0;
}

template <class Key>
void multiset<Key>::recursiveClear(Node *&node) {
  if (node->similar != nullptr) {
    recursiveClear(node->similar);
  }
  if (node->right != nullptr) {
    recursiveClear(node->right);
  }
  if (node->left != nullptr) {
    recursiveClear(node->left);
  }
  delete node;
  node = nullptr;
}

template <class Key>
void multiset<Key>::recursiveCopy(const Node *node) {
  if (node != nullptr) {
    this->insert(node->val);
    this->ms_size += 1;
    if (node->right != nullptr) recursiveCopy(node->right);
    if (node->left != nullptr) recursiveCopy(node->left);
    if (node->similar != nullptr) recursiveCopy(node->similar);
  }
}

template <class Key>
void multiset<Key>::erase(iterator pos) {
  deleteNode(pos.current);
  --ms_size;
}

template <class Key>
void multiset<Key>::swap(multiset &other) {
  this = other;
}

template <class Key>
void multiset<Key>::merge(multiset &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <class Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  size_type count = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) ++count;
  }

  return count;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  iterator it;
  it.current = search(key);
  if (it.current->val != key) it = end();
  return it;
}

template <class Key>
bool multiset<Key>::contains(const Key &key) {
  iterator it;
  it.current = search(key);
  if (it.current->val != key) return false;
  return true;
}

template <class Key>
typename multiset<Key>::iter_pair multiset<Key>::equal_range(const Key &key) {
  iter_pair pair;
  pair.first = lower_bound(key);
  pair.second = upper_bound(key);
  return pair;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  iterator it = find(key);
  while (*it == key) ++it;
  // if (it.current->right != nullptr) ++it;
  return it;
}

template <class Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  iterator it = find(key);
  return it;
}

template <class Key>
template <typename... Args>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::emplace(
    Args &&...args) {
  std::pair<typename multiset<Key>::iterator, bool> result_pair;
  size_type num_of_elements = sizeof...(Args);
  value_type arg_arr[num_of_elements] = {args...};
  iterator res_it;
  for (size_type i = 0; i < num_of_elements; ++i) {
    res_it = insert(arg_arr[i]);
  }
  result_pair.first = res_it;
  result_pair.second = true;
  return result_pair;
}

#ifdef GCOV
template <class Key>
void multiset<Key>::printInOrder() {
  std::cout << "Inorder: " << std::endl;
  if (root == NULL)
    std::cout << "Tree is empty" << std::endl;
  else
    inorder(root);
  std::cout << std::endl;
}
#endif
}  // namespace s21
