namespace s21 {
// Construct
template <typename T>
stack<T>::stack() : _size(0),
                    _head(nullptr) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items) : _size(0),
                                                                  _head(nullptr) {
    for (auto it = items.begin(); it != items.end(); it++) {
        this->push(*it);
    }
}

template <typename T>
stack<T>::stack(const stack &s) : _size(0),
                                  _head(nullptr) {
    if (this != &s && s._size) {
        Node<T> *bufferNode = s._head;

        while (bufferNode->getPastElement()) {
            push(bufferNode->getData());
            bufferNode = bufferNode->getPastElement();
        }

        push(bufferNode->getData());
        reverse();
    }
}

template <typename T>
void stack<T>::reverse() {
    if (_size) {
        Node<T> *previousNode, *currentNode, *nextNode;
        currentNode = _head;
        previousNode = _head;
        currentNode = currentNode->getPastElement();
        previousNode->setPastElement(nullptr);

        while (currentNode != nullptr) {
            nextNode = currentNode->getPastElement();
            currentNode->setPastElement(previousNode);
            previousNode = currentNode;
            currentNode = nextNode;
        }

        _head = previousNode;
    }
}

template <typename T>
stack<T>::stack(stack &&s) : _size(0),
                                         _head(nullptr) {
    if (this != &s) {
        std::swap(_size, s._size);
        std::swap(_head, s._head);
    }
}

//  Destructor
template <typename T>
stack<T>::~stack() {
    while (_head) {
        this->pop();
    }
}

//  Methods
template <typename T>
void stack<T>::push(const_reference value) {
    if (_size > max_size()) {
        throw std::out_of_range("Can`t push! Stack is full");
    }

    Node<T>* bufferNode = new Node<T>(value);

    if (_size) {
        bufferNode->setPastElement(_head);
    }

    setRoot(bufferNode);
    _size++;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
    if (!_size) {
        throw std::out_of_range("Stack is empty");
    }

    return this->_head->Node<T>::getData();
}

template <typename T>
void stack<T>::pop() {
    if (!_size) {
        throw std::out_of_range("Can`t pop! Stack is empty");
    }

    Node<T>* buffer = _head->getPastElement();
    delete _head;
    this->setRoot(buffer);
    _size--;
}

template <typename T>
bool stack<T>::empty() {
    return _size == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
    return _size;
}

template<class T>
void stack<T>::setRoot(Node<T> *element) {
    this->_head = element;
}

template<class T>
void stack<T>::swap(stack<T> &other) {
    if (this != &other) {
        std::swap(_head, other._head);
        std::swap(other._size, _size);
    }
}

//  Overload
template<class T>
stack<T> &stack<T>::operator=(stack<T> &&s) {
    if (this != &s) {
        while (_head) {
            pop();
        }

        std::swap(_size, s._size);
        std::swap(_head, s._head);
    }

    return *this;
}

template<class T>
template <typename... Args>
void stack<T>::emplace_front(Args&&... args) {
    const size_type sizeArgs = sizeof...(Args);
    value_type argsArray[sizeArgs] = {args...};

    for (size_type i = 0; i < sizeArgs; ++i) {
        push(argsArray[i]);
    }
}

template <typename T>
typename s21::stack<T>::size_type stack<T>::max_size() {
  return std::numeric_limits<size_t>::max() / (sizeof(Node<T>));
}
}  //  namespace s21
