namespace s21 {
//  Construct
template <typename T>
Node<T>::Node(const T &value) : _data(value),
                                _pastElement(nullptr) {}

//  Destruct
template <typename T>
Node<T>::~Node() {}

//  Getes
template<class T>
Node<T>* Node<T>::getPastElement() {
    return _pastElement;
}

template <typename T>
void Node<T>::setPastElement(Node *element) {
    this->_pastElement = element;
}

template<class T>
const T &Node<T>::getData() {
    return this->_data;
}
}  //  namespace s21
