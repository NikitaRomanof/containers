namespace s21 {
template <class T, size_t L>
array<T, L>::array() : _size(L) {
}

template <class T, size_t L>
array<T, L>::array(std::initializer_list<value_type> const &items) : _size(L) {
    if (_size < items.size()) {
        throw std::invalid_argument("Other arrays size");
    }

    size_t i = 0;

    for (auto it = items.begin(); it != items.end(); ++it, ++i) {
        _array[i] = *it;
    }
}

template <class T, size_t L>
array<T, L>::array(const array &a) : _size(L) {
    if (_size != a._size) {
        throw std::invalid_argument("Other arrays size");
    }

    if (this != &a) {
        size_t i = 0;

        for (iterator it = begin(); it != end(); ++it, ++i) {
            *it = a._array[i];
        }
    }
}

template <class T, size_t L>
array<T, L>::array(array &&a) : _size(L) {
    if (_size != a._size) {
        throw std::invalid_argument("Other arrays size");
    }

    if (this != &a) {
        std::swap(_array, a._array);
        std::swap(_size, a._size);
    }
}

template <class T, size_t L>
array<T, L>::~array() {}

template <class T, size_t L>
array<T, L> &array<T, L>::operator=(array &&s) {
    if (_size != s._size) {
        throw std::invalid_argument("Other arrays size");
    }

    if (this != &s) {
        std::swap(s._array, _array);
        std::swap(s._size, _size);
    }

    return *this;
}

template <class T, size_t L>
typename array<T, L>::reference array<T, L>::at(size_type pos) {
    if (pos >= _size) {
        throw std::invalid_argument("Invalid argument");
    }

    return _array[pos];
}

template <class T, size_t L>
typename array<T, L>::reference array<T, L>::operator[](size_type pos) {
    return at(pos);
}

template <class T, size_t L>
typename array<T, L>::const_reference array<T, L>::front() {
    if (_size == 0) {
        throw std::invalid_argument("Empty array");
    }

    return _array[0];
}

template <class T, size_t L>
typename array<T, L>::const_reference array<T, L>::back() {
    if (_size == 0) {
        throw std::invalid_argument("Empty array");
    }

    return _array[_size -1];
}

template <class T, size_t L>
typename array<T, L>::iterator array<T, L>::data() {
    return _array;
}

template <class T, size_t L>
typename array<T, L>::iterator array<T, L>::begin() {
    return iterator(&_array[0]);
}

template <class T, size_t L>
typename array<T, L>::iterator array<T, L>::end() {
    return iterator(&_array[_size]);
}

template <class T, size_t L>
bool array<T, L>::empty() {
    return _size == 0;
}

template <class T, size_t L>
typename array<T, L>::size_type array<T, L>::size() {
    return _size;
}

template <class T, size_t L>
typename array<T, L>::size_type array<T, L>::max_size() {
  return _size;
}

template <class T, size_t L>
void array<T, L>::swap(array& other) {
    if (_size != other._size) {
        throw std::invalid_argument("Other arrays size");
    }

    if (this != &other) {
        std::swap(_array, other._array);
        std::swap(_size, other._size);
    }
}

template <class T, size_t L>
void array<T, L>::fill(typename array<T, L>::const_reference value) {
    if (_size == 0) {
        throw std::invalid_argument("Empty array");
    }

    for (iterator it = begin(); it != end(); ++it) {
            *it = value;
    }
}
}  //  namespace s21
