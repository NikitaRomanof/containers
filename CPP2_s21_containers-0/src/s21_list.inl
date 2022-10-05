namespace s21 {
/* ---------------------LIST FUNCTIONS--------------------- */
template <typename T>
List<T>::List() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
List<T>::List(size_type n) : _size(0), _head(nullptr), _tail(nullptr) {
  if (n >= max_size()) {
    throw std::invalid_argument("ERROR on constructor, n >= max_size");
  }
  while (n) {
    push_back(value_type());
    n--;
  }
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items)
    : _size(0), _head(nullptr), _tail(nullptr) {
  if (items.size() >= max_size()) {
    throw std::invalid_argument("ERROR on constructor, n >= max_size");
  }
  for (value_type value : items) {
    push_back(value);
  }
}

template <typename T>
List<T>::List(const List &l) : _size(0), _head(nullptr), _tail(nullptr) {
  if (this != &l) {
    Node *curr = l._head;
    while (curr != nullptr) {
      push_back(curr->_data);
      curr = curr->_pNext;
    }
  }
}

template <typename T>
List<T>::List(List &&l) : _size(0), _head(nullptr), _tail(nullptr) {
  *this = std::move(l);
}

template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&l) {
  clear();
  swap(l);
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &l) {
  if (this == &l) {
    throw std::invalid_argument("Assigning an object to itself");
  }
  clear();
  ListIterator iter(l);
  while (iter._curIter != nullptr) {
    push_back(*iter);
    ++iter;
  }
  return *this;
}

/* --------------LIST ELEMENT ACCESS-------------- */
template <typename T>
const T &List<T>::front() {
  if (_size == 0) {
    throw std::out_of_range("Error function front(), List is empty");
  }
  return _head->_data;
}

template <typename T>
const T &List<T>::back() {
  if (_size == 0) {
    throw std::out_of_range("Error function back(, List is empty");
  }
  return _tail->_data;
}

/* ---------------------LIST MODIFIERS--------------------- */
template <typename T>
void List<T>::clear() {
  while (_head != nullptr) {
    Node *del = _head;
    _head = _head->_pNext;
    delete del;
    del = nullptr;
  }
  _head = nullptr;
  _tail = nullptr;
  _size = 0;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  if (_size == max_size()) {
    throw std::out_of_range(
        "ERROR on function push_back(). Cannot add item, list is full");
  }
  if (_head == nullptr) {
    _head = new Node(value);
    _tail = _head;
  } else {
    if (_tail == _head) {
      _tail = new Node(value, nullptr, _head);
      _head->_pNext = _tail;
    } else {
      Node *curr = new Node(value, nullptr, _tail);
      _tail->_pNext = curr;
      _tail = curr;
    }
  }
  _size++;
}

template <typename T>
void List<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range(
        "ERROR on function pop_back(). Cannot delete item, list is empty");
  }
  if (_tail->_pPrev == nullptr) {  //  в случае удаления единственного элемента
    clear();
  } else {
    Node *del = _tail;
    _tail = _tail->_pPrev;
    _tail->_pNext = nullptr;
    delete del;
    _size--;
  }
}

template <typename T>
void List<T>::push_front(const_reference value) {
  if (_size == max_size()) {
    throw std::out_of_range(
        "ERROR on function push_front(). Cannot add item, list is full");
  }
  if (_head == nullptr) {
    _head = new Node(value);
    _tail = _head;
  } else {
    if (_tail == _head) {
      _head = new Node(value, _tail, nullptr);
      _tail->_pPrev = _head;
    } else {
      Node *curr = new Node(value, _head, nullptr);
      _head->_pPrev = curr;
      _head = curr;
    }
  }
  _size++;
}

template <typename T>
void List<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range(
        "ERROR on function pop_back(). Cannot delete item, list is empty");
  }
  if (_head->_pNext == nullptr) {  //  в случае удаления единственного элемента
    clear();
  } else {
    Node *del = _head;
    _head = _head->_pNext;
    _head->_pPrev = nullptr;
    delete del;
    _size--;
  }
}

template <typename T>
void List<T>::swap(List &other) {
  if (this == &other) {
    throw std::invalid_argument(
        "ERROR on function swap(). The current and added lists are one "
        "object");
  }
  std::swap(_head, other._head);
  std::swap(_tail, other._tail);
  std::swap(_size, other._size);
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos._curIter == nullptr) {
    throw std::invalid_argument(
        "ERROR on function erase(). Cannot delete item, iterator points to "
        "nullptr");
  }
  if (pos._curIter->_pNext == nullptr) {
    pop_back();
  } else if (pos._curIter->_pPrev == nullptr) {
    pop_front();
  } else {
    Node *del = pos._curIter;
    del->_pPrev->_pNext = del->_pNext;
    del->_pNext->_pPrev = del->_pPrev;
    delete del;
    _size--;
  }
}

template <typename T>
typename List<T>::ListIterator List<T>::insert(iterator pos,
                                               const_reference value) {
  if (_size == max_size()) {
    throw std::out_of_range(
        "ERROR on function insert(). Cannot add item, list is full");
  }
  if (pos._curIter == nullptr) {
    throw std::invalid_argument(
        "ERROR on function insert(). Iterator points to nullptr");
  }
  Node *buf = new Node(value, pos._curIter, pos._curIter->_pPrev);
  if (pos._curIter->_pNext == nullptr) {
    _tail = pos._curIter;
  }
  if (pos._curIter->_pPrev == nullptr) {
    _head = buf;
  } else {
    pos._curIter->_pPrev->_pNext = buf;
  }
  pos._curIter->_pPrev = buf;
  _size++;
  iterator rez(*this);
  rez._curIter = buf;
  return rez;
}

template <typename T>
void List<T>::sort() {
  if (empty()) {
    throw std::invalid_argument("ERROR on function sort(). List is empty");
  }
  iterator start = begin();
  iterator finish = end();
  for (; start != --finish;) {
    for (iterator i = start; i != finish; ++i) {
      if (i._curIter->_data > i._curIter->_pNext->_data) {
        std::swap(i._curIter->_data, i._curIter->_pNext->_data);
      }
    }
  }
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  if (_size + other._size >= max_size()) {
    throw std::out_of_range(
        "ERROR on function splice(). Cannot add item, list is full");
  }
  if (empty() || other.empty()) {
    throw std::invalid_argument(
        "ERROR on function splice(). This/add list is empty");
  }
  if (pos._curIter == nullptr) {
    throw std::invalid_argument(
        "ERROR on function splice(). Iterator points to nullptr");
  }
  if (this == &other) {
    throw std::invalid_argument(
        "ERROR on function splice(). The current and added lists are one "
        "object");
  }
  List *buffer = new List(std::move(other));
  if (_tail->_pPrev == nullptr) {
    _tail = pos._curIter;
  }
  if (pos._curIter->_pPrev == nullptr) {
    _head = buffer->_head;
  } else {
    pos._curIter->_pPrev->_pNext = buffer->_head;
    buffer->_head->_pPrev = pos._curIter->_pPrev;
  }
  buffer->_tail->_pNext = pos._curIter;
  pos._curIter->_pPrev = buffer->_tail;
  _size += buffer->_size;
  buffer->_head = nullptr;
  buffer->_tail = nullptr;
  delete buffer;
  buffer = nullptr;
}

template <typename T>
void s21::List<T>::merge(List &other) {
  if (empty()) {
    *this = std::move(other);
  } else {
    const_iterator iter = cbegin();
    splice(iter, other);
  }
  sort();
}

template <typename T>
void List<T>::reverse() {
  if (empty()) {
    throw std::invalid_argument("ERROR on function reverse(). List is empty");
  }
  iterator start = begin();
  iterator finish = end();
  while (start != --finish) {
    for (iterator it = start; it != finish; ++it) {
      std::swap(it._curIter->_data, it._curIter->_pNext->_data);
    }
  }
}

template <typename T>
void List<T>::unique() {
  iterator start = begin();
  while (start._curIter != nullptr && start._curIter->_pNext != nullptr) {
    while (start._curIter->_data == start._curIter->_pNext->_data) {
      iterator buf = start;  //  костыль под убунту
      --start;
      this->erase(buf);
    }
    ++start;
  }
}

/* --------------LIST CAPACITY-------------- */
template <typename T>
bool List<T>::empty() {
  return _size == 0;
}

template <typename T>
size_t List<T>::size() {
  return _size;
}

template <typename T>
size_t List<T>::max_size() {
  return (std::numeric_limits<size_type>::max() / (sizeof(Node))) / 2;
}

/* --------------INNER CLAS ITERATOR-------------- */
template <typename T>
List<T>::ListIterator::ListIterator() {
  _curIter = nullptr;
  _listHead = nullptr;
  _listTail = nullptr;
}

template <typename T>
List<T>::ListIterator::ListIterator(const List<T> &other) {
  if (other._size == 0) {
    throw std::invalid_argument("List is empty");
  }
  _curIter = other._head;
  _listHead = other._head;
  _listTail = other._tail;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++() {
  if (_listHead == nullptr && _curIter == nullptr) {
    throw std::invalid_argument(
        "Operation ++ is not possible, iterator is nullptr");
  }
  if (_curIter == nullptr) {
    _curIter = _listHead;
  } else {
    _curIter = _curIter->_pNext;
  }
  return *this;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--() {
  if (_listTail == nullptr && _curIter == nullptr) {
    throw std::invalid_argument(
        "Operation -- is not possible, iterator is nullptr");
  }
  if (_curIter == nullptr) {
    _curIter = _listTail;
  } else {
    _curIter = _curIter->_pPrev;
  }
  return *this;
}

template <typename T>
T &List<T>::ListIterator::operator*() {
  if (_curIter == nullptr) {
    throw std::invalid_argument(
        "Operation * is not possible, pointer is nullptr");
  }
  return _curIter->_data;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator &other) {
  return _curIter != other._curIter;
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator &other) {
  return _curIter == other._curIter;
}

/* --------------INNER CLASS CONST_ITERATOR-------------- */
template <typename T>
const T &List<T>::ListConstIterator::operator*() const {
  if (this->_curIter == nullptr) {
    throw std::invalid_argument(
        "Operation * is not possible, pointer is nullptr");
  }
  return this->_curIter->_data;
}

template <typename T>
typename List<T>::ListConstIterator &List<T>::ListConstIterator::operator=(
    const ListIterator &other) {
  this->_listHead = other._listHead;
  this->_curIter = other._curIter;
  this->_listTail = other._listTail;
  return *this;
}

/* --------------LIST FUNC. ITERATORS-------------- */
template <typename T>
typename List<T>::iterator List<T>::end() {
  if (empty()) {
    throw std::out_of_range("Operation end() is not possible, list is empty");
  }
  iterator iter(*this);
  iter._curIter = iter._listTail->_pNext;
  return iter;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  if (empty()) {
    throw std::out_of_range("Operation end() is not possible, list is empty");
  }
  iterator iter(*this);
  return iter;
}

template <typename T>
typename List<T>::const_iterator List<T>::cend() {
  if (empty()) {
    throw std::out_of_range("Operation end() is not possible, list is empty");
  }
  const_iterator iter(*this);
  iter._curIter = iter._listTail->_pNext;
  return iter;
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin() {
  if (empty()) {
    throw std::out_of_range("Operation end() is not possible, list is empty");
  }
  const_iterator iter(*this);
  return iter;
}

/* --------------BONUS-------------- */
template <typename T>
template <typename... Args>
void List<T>::emplace_back(Args &&...args) {
  const size_type sizeArgs = sizeof...(Args);
  value_type masArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; i++) {
    push_back(masArgs[i]);
  }
}

template <typename T>
template <typename... Args>
void List<T>::emplace_front(Args &&...args) {
  const size_type sizeArgs = sizeof...(Args);
  value_type masArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; i++) {
    push_front(masArgs[i]);
  }
}

template <typename T>
template <typename... Args>
typename List<T>::ListIterator List<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  const size_type sizeArgs = sizeof...(Args);
  value_type masArgs[sizeArgs] = {args...};
  for (size_type i = 0; i < sizeArgs; i++) {
    insert(pos, masArgs[i]);
  }
  return pos;
}

}  // namespace s21
