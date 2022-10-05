namespace s21 {

// Member functions

template <class T>
set<T>::set() : _root(nullptr), _size(0U) {}

template <class T>
set<T>::set(std::initializer_list<value_type> const &items) : set<T>::set() {
  auto it = items.begin();
  while (it < items.end()) {
    s21_set_isfull(1);
    insert(*it);
    ++it;
  }
}

template <class T>
set<T>::set(const set &s) : _root(nullptr), _size(0U) {
  if (_root != s._root && s._size != 0) {
    s21_tree_copy(s._root, this);
  }
}

template <class T>
set<T>::set(set &&s) : _root(nullptr), _size(0U) {
  swap(s);
}

template <class T>
set<T>::~set() {
  s21_tree_del(&_root);
}

template <class T>
set<T> &set<T>::operator=(set &&s) {
  if (_root != s._root && s._size != 0) {
    s21_tree_del(&_root);
    swap(s);
  }
  return *this;
}

// Iterators

template <class T>
set<T>::set_iter::set_iter() {
  _pos = nullptr;
}

template <class T>
void set<T>::set_iter::operator=(const_iterator &it) {
  if (*this != it) {
    _pos = it._pos;
  }
}

template <class T>
typename set<T>::const_reference set<T>::set_iter::operator*() {
  if (_pos == nullptr) throw std::out_of_range("NULL PTR");
  return _pos->getKey();
}

template <class T>
void set<T>::set_iter::operator--() {
  set prev_set;
  node_type *prev_tree;
  value_type max_prev_key = _pos->getKey();
  prev_tree = prev_set.s21_tree_prev(_pos, _pos->getKey(), &max_prev_key);
  _pos = prev_tree;
}

template <class T>
void set<T>::set_iter::operator++() {
  set next_set;
  node_type *next_tree;
  value_type min_next_key = _pos->getKey();
  next_tree = next_set.s21_tree_next(_pos, _pos->getKey(), &min_next_key);
  _pos = next_tree;
}

template <class T>
bool set<T>::set_iter::operator==(const_iterator &it) {
  return _pos == it._pos;
}

template <class T>
bool set<T>::set_iter::operator!=(const_iterator &it) {
  return !(*this == it);
}

template <class T>
typename set<T>::iterator set<T>::begin() {
  iterator res;
  if (!empty()) res._pos = s21_tree_begin();
  return res;
}

template <class T>
typename set<T>::iterator set<T>::end() {
  iterator res;
  if (!empty()) res._pos = s21_tree_end();
  return res;
}

// Set Capacity

template <class T>
bool set<T>::empty() {
  return (_root == nullptr);
}

template <class T>
typename set<T>::size_type set<T>::size() {
  return _size;
}

template <class T>
typename set<T>::size_type set<T>::max_size() {
  return std::numeric_limits<size_type>::max() / (sizeof(node_type));
}

// Modifiers

template <class T>
void set<T>::clear() {
  s21_tree_del(&_root);
}

template <class T>
typename std::pair<typename s21::set<T>::iterator, bool> set<T>::insert(
    const_reference value) {
  iterator it;
  pair_type res(it, false);
  s21_set_isfull(1);
  if (_root == nullptr) {
    _root = new node_type(value, nullptr, nullptr, nullptr);
    ++_size;
    it._pos = _root;
    res.first = it;
    res.second = true;
  } else {
    if (s21_tree_contains(_root, value)) {
      it._pos = nullptr;
      res.first = it;
      res.second = false;
    } else {
      res = s21_tree_insert(_root, value);
      if (res.second) {
        ++_size;
      }
    }
  }
  return res;
}

template <class T>
void set<T>::erase(iterator pos) {
  if (pos._pos != nullptr) {
    s21_tree_erase(pos._pos);
  }
}

template <class T>
void set<T>::swap(set &other) {
  if (_root != other._root && other._size != 0) {
    std::swap(_root, other._root);
    std::swap(_size, other._size);
  }
}

template <class T>
void set<T>::merge(set &other) {
  if (other._root != nullptr) {
    s21_set_isfull(other._size);
    iterator it = other.begin();
    pair_type res;
    size_type max = other.size();
    set success;
    for (size_type i = 0; i < max; ++i, ++it) {
      res = insert(*it);
      if (res.second) {
        success.insert(*it);
      }
    }
    s21_tree_clear_merge(&other, &success);
  }
}

// Lookup

template <class T>
typename set<T>::iterator set<T>::find(const_reference key) {
  iterator res;
  res._pos = s21_tree_find(_root, key);
  return res;
}

template <class T>
bool set<T>::contains(const_reference key) {
  return s21_tree_contains(_root, key);
}

// Bonus

template <class T>
template <class... Args>
std::pair<typename s21::set<T>::iterator, bool> set<T>::emplace(
    Args &&...args) {
  pair_type res;
  std::vector<value_type> arg_vect = {args...};
  auto it = arg_vect.begin();
  while (it < arg_vect.end()) {
    res = insert(*it);
    ++it;
  }
  return res;
}

// support

template <class T>
void set<T>::s21_set_isfull(size_t num) {
  if (_size + num >= max_size()) throw std::length_error("Set is full");
}

template <class T>
void set<T>::s21_print_set() {
  if (_root != nullptr) {
    std::cout << "size: " << _size << " | ptr: " << _root << std::endl;
    s21_print_tree(_root);
    std::cout << std::endl;
  }
}

template <class T>
void set<T>::s21_print_tree(node_type *tree) {
  if (tree != nullptr) {
    s21_print_tree(tree->getLeft());
    std::cout << tree->getKey() << " ";
    s21_print_tree(tree->getRight());
  }
}

// Tree

template <class T>
void set<T>::s21_tree_copy(node_type *tree, set *set_new) {
  if (tree != nullptr) {
    set_new->s21_set_isfull(1);
    set_new->insert(tree->getKey());
    s21_tree_copy(tree->getLeft(), set_new);
    s21_tree_copy(tree->getRight(), set_new);
  }
}

template <class T>
void set<T>::s21_tree_del(node_type **tree) {
  if (*tree != nullptr) {
    node_type *left = (*tree)->getLeft();
    s21_tree_del(&left);
    node_type *right = (*tree)->getRight();
    s21_tree_del(&right);
    --_size;
    delete *tree;
    *tree = nullptr;
  }
}

template <class T>
void set<T>::s21_tree_erase(node_type *tree) {
  if (tree != nullptr) {
    if (_root == tree || tree->getParent() == nullptr) {
      _root = tree->getLeft();
      if (_root != nullptr) _root->setParent(nullptr);
      tree->setLeft(nullptr);
      s21_tree_copy(tree->getRight(), this);
      s21_tree_del(&tree);
    } else {
      if (tree->getParent()->getLeft() == tree) {
        tree->getParent()->setLeft(nullptr);
      }
      if (tree->getParent()->getRight() == tree) {
        tree->getParent()->setRight(nullptr);
      }
      s21_tree_copy(tree->getLeft(), this);
      s21_tree_copy(tree->getRight(), this);
      s21_tree_del(&tree);
    }
  }
}

template <class T>
typename set<T>::node_type *set<T>::s21_tree_begin() {
  node_type *res = _root;
  if (res != nullptr) {
    while (res->getLeft() != nullptr) {
      res = res->getLeft();
    }
  }
  return res;
}

template <class T>
typename set<T>::node_type *set<T>::s21_tree_end() {
  node_type *res = _root;
  if (res != nullptr) {
    while (res->getRight() != nullptr) {
      res = res->getRight();
    }
  }
  return res;
}

template <class T>
typename set<T>::node_type *set<T>::s21_tree_prev(node_type *tree,
                                                  const_value_type &key,
                                                  value_type *max_prev_key) {
  node_type *res = nullptr;
  if (tree != nullptr) {
    if ((*max_prev_key == key && tree->getKey() < key) ||
        (*max_prev_key<key && * max_prev_key> tree->getKey()))
      *max_prev_key = tree->getKey();
    if (tree->getRight() != nullptr && (tree->getRight())->getKey() < key) {
      if ((*max_prev_key != key &&
           (tree->getRight())->getKey() > *max_prev_key) ||
          (*max_prev_key == key))
        res = s21_tree_prev(tree->getRight(), key, max_prev_key);
    }
    if (res == nullptr && tree->getLeft() != nullptr &&
        tree->getLeft()->getKey() < key) {
      if ((*max_prev_key != key && tree->getLeft()->getKey() > *max_prev_key) ||
          (*max_prev_key == key))
        res = s21_tree_prev(tree->getLeft(), key, max_prev_key);
    }
    if (res == nullptr && tree->getParent() != nullptr &&
        *max_prev_key == key) {
      if ((tree->getParent())->getKey() > *max_prev_key || *max_prev_key == key)
        res = s21_tree_prev(tree->getParent(), key, max_prev_key);
    }
    if (res == nullptr) {
      res = tree;
    }
  }
  return res;
}

template <class T>
typename set<T>::node_type *set<T>::s21_tree_next(node_type *tree,
                                                  const_value_type &key,
                                                  value_type *min_next_key) {
  node_type *res = nullptr;
  if (tree != nullptr) {
    if ((*min_next_key == key && tree->getKey() > key) ||
        (*min_next_key > key && *min_next_key < tree->getKey()))
      *min_next_key = tree->getKey();
    if (tree->getLeft() != nullptr && tree->getLeft()->getKey() > key) {
      if ((*min_next_key != key && tree->getLeft()->getKey() < *min_next_key) ||
          (*min_next_key == key))
        res = s21_tree_next(tree->getLeft(), key, min_next_key);
    }
    if (res == nullptr && tree->getRight() != nullptr &&
        tree->getRight()->getKey() > key) {
      if ((*min_next_key != key &&
           tree->getRight()->getKey() < *min_next_key) ||
          (*min_next_key == key))
        res = s21_tree_next(tree->getRight(), key, min_next_key);
    }
    if (res == nullptr && tree->getParent() != nullptr &&
        *min_next_key == key) {
      if (tree->getParent()->getKey() < *min_next_key || *min_next_key == key)
        res = s21_tree_next(tree->getParent(), key, min_next_key);
    }
    if (res == nullptr) {
      res = tree;
    }
  }
  return res;
}

template <class T>
typename set<T>::node_type *set<T>::s21_tree_find(node_type *tree,
                                                  const_value_type &key) {
  node_type *res = nullptr;
  if (tree != nullptr) {
    if (tree->getKey() == key) res = tree;
    if (res == nullptr) res = s21_tree_find(tree->getLeft(), key);
    if (res == nullptr) res = s21_tree_find(tree->getRight(), key);
  }
  return res;
}

template <class T>
bool set<T>::s21_tree_contains(node_type *tree, const_value_type &key) {
  bool res(false);
  if (tree != nullptr) {
    if (tree->getKey() && tree->getKey() == key) {
      res = true;
    } else {
      if (tree->getLeft() != nullptr)
        res = s21_tree_contains(tree->getLeft(), key);
      if (!res && tree->getRight() != nullptr)
        res = s21_tree_contains(tree->getRight(), key);
    }
  }
  return res;
}

template <class T>
typename std::pair<typename s21::set<T>::iterator, bool>
set<T>::s21_tree_insert(node_type *tree, const_value_type &key) {
  pair_type res;
  if (tree->getKey() > key && tree->getLeft() != nullptr) {
    res = s21_tree_insert(tree->getLeft(), key);
  } else if (tree->getKey() < key && tree->getRight() != nullptr) {
    res = s21_tree_insert(tree->getRight(), key);
  } else {
    node_type *new_tree = new node_type(key, tree, nullptr, nullptr);
    if (tree->getKey() > key) {
      tree->setLeft(new_tree);
    } else {
      tree->setRight(new_tree);
    }
    iterator it;
    it._pos = new_tree;
    res.first = it;
    res.second = true;
  }
  return res;
}

template <class T>
void set<T>::s21_tree_clear_merge(set *other, set *tree_success) {
  if (other->_root != nullptr && tree_success->_root != nullptr) {
    iterator it = tree_success->begin();
    size_type max = other->size();
    for (size_type i = 0; i < max; ++i, ++it) {
      if (other->contains(*it)) other->erase(other->find(*it));
    }
  }
}

}  // namespace s21
