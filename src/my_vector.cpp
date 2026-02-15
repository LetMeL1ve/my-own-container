#include "my_vector.hpp"

// Implementing a constructor with size argument.
template <typename T>
MyVector<T>::MyVector(size_t size) {
    _data = new T[size];
    _size = size;
    _capacity = size;
}

// Implementing a default constructor.
template <typename T>
MyVector<T>::MyVector() {
    _size = 0;
    _capacity = 1;
    _data = new T[_capacity];
}

// Implementing copy constructor.
template <typename T>
MyVector<T>::MyVector(const MyVector& obj) {
    _data = obj.data();
    _size = obj.size();
    _capacity = obj.capacity();
}

// Implementing move constructor.
template <typename T>
MyVector<T>::MyVector(MyVector&& obj) {
    _data = obj.data();
    _size = obj.size();
    _capacity = obj.capacity();

    obj._capacity = 0;
    obj._size = 0;
    delete[] obj._data;
}
// Implementing destructor.
template <typename T>
MyVector<T>::~MyVector() {
    delete[] _data;
}