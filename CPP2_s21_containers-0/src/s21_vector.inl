
namespace s21 {
// constructors
template <class T>  // simple comstructor
Vector<T>::Vector() : _size(0UL), _capacity(0UL), arr(nullptr) {}

template <class T>  // init size constructor
Vector<T>::Vector(size_type n)
    : _size(n), _capacity(n), arr(n ? new T[n] : nullptr) {}

template <class T>
Vector<T>::Vector(std::initializer_list<value_type> const &items)
    : _size(items.size()), _capacity(items.size()), arr(nullptr) {
  arr = new T[items.size()];
  uint32_t i = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    arr[i++] = *it;
  }
}

template <typename T>  // copy constructor
Vector<T>::Vector(const Vector<T> &v)
    : _size(v._size), _capacity(v._capacity), arr(nullptr) {
  *this = v;
}

template <typename T>  // move constructor
Vector<T>::Vector(Vector<T> &&v) : _size(0), _capacity(0), arr(nullptr) {
  *this = std::move(v);
}

// destructor
template <typename T>
Vector<T>::~Vector() {
  clear();
}

// methods for accessing container elements

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&v) {
  if (&v == this) {
    throw std::invalid_argument("Dont move anything into itelf");
  }
  clear();
  swap(v);
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
  if (this == &v) {
    throw std::invalid_argument(
        "Error in operator= copy. Assigning an object to itself");
  }
  clear();
  arr = new value_type[v._capacity];
  _capacity = v._capacity;
  for (size_t i = 0; i < v._size; i++) {
    arr[i] = v.arr[i];
  }
  _size = v._size;
  return *this;
}

template <typename T>
typename s21::Vector<T>::reference Vector<T>::at(size_type pos) {
  if (!(pos < _size)) {
    throw std::out_of_range("Invalid index, more then vector size");
  }
  return arr[pos];
}

template <typename T>
typename s21::Vector<T>::reference Vector<T>::operator[](size_type pos) {
  if (pos > _size) {
    if (pos > _capacity) {
      throw std::out_of_range("Position of element out of size");
    }
  }
  return arr[pos];
}

template <typename T>
typename s21::Vector<T>::const_reference Vector<T>::front() {
  if (_size < 1) {
    throw std::out_of_range("Cannot get front element in empty vector");
  }
  return arr[0];
}

template <typename T>
typename s21::Vector<T>::const_reference Vector<T>::back() {
  if (_size < 1) {
    throw std::out_of_range("Cannot get back element in empty vector");
  }
  return arr[_size - 1];
}

template <typename T>
typename s21::Vector<T>::iterator Vector<T>::data() {
  return arr;
}

// methods for checking if a container is full
template <typename T>
bool Vector<T>::empty() {
  return _size == 0;
}

template <typename T>
typename s21::Vector<T>::size_type Vector<T>::size() {
  return _size;
}

template <typename T>
typename s21::Vector<T>::size_type Vector<T>::max_size() {
  return std::numeric_limits<size_t>::max() / (sizeof(this));
}

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size >= max_size()) {
    throw std::out_of_range("Cannot allocate such memory amount");
  }
  if (size <= _capacity) return;
  value_type *ptr = new value_type[size]();
  for (size_type i = 0; i < _size; ++i) {
    ptr[i] = arr[i];
  }
  if (arr) {
    delete[] arr;
    arr = nullptr;
  }
  arr = ptr;
  _capacity = size;
}

template <typename T>
typename s21::Vector<T>::size_type Vector<T>::capacity() {
  return _capacity;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (_capacity > _size) {
    value_type *ptr = new value_type[_size]();
    for (size_type i = 0; i < _size; ++i) {
      ptr[i] = arr[i];
    }
    if (arr) {
      delete[] arr;
      arr = nullptr;
    }
    arr = ptr;
    _capacity = _size;
  }
}

// methods for dealing with the container iterator

template <typename T>
typename s21::Vector<T>::iterator Vector<T>::begin() {
  return iterator(arr);
}

template <typename T>
typename s21::Vector<T>::iterator Vector<T>::end() {
  return iterator(&arr[_size]);
}

// methods for changing the container
template <typename T>
void Vector<T>::clear() {
  if (arr) {
    delete[] arr;
    arr = nullptr;
  }
  _size = 0;
  _capacity = 0;
}

template <typename T>
typename s21::Vector<T>::iterator Vector<T>::insert(iterator pos,
                                                    const_reference value) {
  if (pos == nullptr) {
    throw std::out_of_range("Do not insert to nullptr, try another place");
  }
  size_type pos1 = pos - begin();
  if (pos1 >= max_size()) {
    throw std::out_of_range("Invalid position, out of memory");
  }
  ++_size;
  value_type *ptr = doubleCapacity(&_capacity, _size);
  size_type i = 0;
  for (; i < pos1; ++i) {
    ptr[i] = arr[i];
  }
  ptr[i++] = value;
  for (; i < _size; ++i) {
    ptr[i] = arr[i - 1];
  }
  if (arr) {
    delete[] arr;
    arr = nullptr;
  }
  arr = ptr;
  return &arr[i];
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  if (pos == nullptr) {
    throw std::out_of_range("cannot erase element from null pointer");
  }
  if (empty()) {
    throw std::out_of_range("Cannot erase element from empty vector");
  }
  --_size;
  size_type i = pos - begin();
  for (; i < _size; ++i) {
    arr[i] = arr[i + 1];
  }
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (_size == max_size()) {
    throw std::out_of_range("Cannot push element - memory is full");
  }
  ++_size;
  value_type *ptr = doubleCapacity(&_capacity, _size);
  for (size_t i = 0; i < _size - 1; i++) {
    ptr[i] = arr[i];
  }
  if (arr) {
    delete[] arr;
    arr = nullptr;
  }
  arr = ptr;
  arr[_size - 1] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Cannot reduce empty vector");
  }
  --_size;
}

template <typename T>
void Vector<T>::swap(Vector<T> &other) {
  if (&other == this) {
    throw std::invalid_argument("Do not swap argument itself");
  }
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
  std::swap(arr, other.arr);
}

template <typename T>
template <typename... Args>
typename s21::Vector<T>::iterator Vector<T>::emplace(const_iterator pos,
                                                     Args &&...args) {
  size_type arg_size = sizeof...(args);
  if (_size + arg_size >= max_size()) {
    throw std::length_error("Cannot allocate memory for new elements");
  }
  s21::Vector<T> tmp_vec{args...};
  auto element = tmp_vec.begin();
  iterator pos1 = const_cast<T *>(pos);
  while (element != tmp_vec.end()) {
    insert(pos1, *element);
    ++element;
  }
  return iterator(pos);
}

template <typename T>
template <typename... Args>
void s21::Vector<T>::emplace_back(Args &&...args) {
  s21::Vector<T> tmp_vec{args...};
  auto element = tmp_vec.begin();
  while (element != tmp_vec.end()) {
    push_back(*element);
    ++element;
  }
}

template <typename T>
T *Vector<T>::doubleCapacity(size_type *capacity, size_type size) {
  if (*capacity < size) {
    if (*capacity > (max_size() / 2)) {
      throw std::out_of_range(
          "You want too much of memory. Capacity cannot be doubled");
    }
    *capacity *= 2;
  }
  T *ptr = new value_type[*capacity]();
  return ptr;
}

}  // namespace s21
