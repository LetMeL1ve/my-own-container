#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* _data;  // Dynamic array which stores all of the values.

    size_t _size;  // Current size of vector.
    size_t _capacity;  // Number of elements which are memory reserved for.

    // Used in copy assignment operator.
    void swap(MyVector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }
public:

    #pragma region  Constructors, destructors and assignment operators
    // Default constructor.
    MyVector() : _data(new T[1]), _size(0), _capacity(1) {}

    // Constructor with size.
    MyVector(size_t size) : _data(new T[size] {}), _size(size), _capacity(size) {
    }

    // Copy constructor.
    MyVector(const MyVector& other) : _size(other._size), _capacity(other._capacity) {
        _data = new T[_capacity];

        for (size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }

    // Move constructor.
    MyVector(MyVector&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {  
        // Clearing old object.
        other._capacity = 0;
        other._size = 0;
        other._data = nullptr;
    }

    ~MyVector() noexcept { delete[] _data; }  // Destructor.

    // Copy assingment operator.
    MyVector& operator=(const MyVector& other) {
        if (this != &other) { // Self providing checking.
            MyVector temp(other);
            swap(temp);
        }

        return *this;
    }

    // Move assingment operator.
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other)  // Self providing checking.
            swap(other);

        return *this;
    }

    #pragma endregion
    
    #pragma region  All functions and operators for data getting
    // Getters.
    T* data() noexcept { return _data; }
    const T* data() const noexcept  { return _data; }
    size_t capacity() const noexcept { return _capacity; }
    size_t size() const noexcept { return _size; }

    // Returns ```true``` if size is 0.
    bool empty() const noexcept { return _size == 0; }

    // Returns a refrence to element at ```index``` position. Posible UB if index is out of range.
    T& operator[](size_t index) { return _data[index]; }
    // Const variation.
    const T& operator[](size_t index) const { return _data[index]; }

    // Returns a refrence to element at ```index``` position. Throws std::exception if index is out of range of vector.
    T& at(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range."); // Index checking.
        return _data[index];  // Returning.
    }
    // Const variation.
    const T& at(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range."); // Index checking.
        return _data[index];  // Returning.
    }

    // Returns a refrence to first element. If vector is empty throws std::exception.
    T& front() {
        if (_size == 0) throw std::logic_error("Vector is empty.");
        return _data[0];
    }
    // Const version.
    const T& front() const {
        if (_size == 0) throw std::logic_error("Vector is empty.");
        return _data[0];
    }

    // Returns a refrence to last element. If vector is empty throws std::exception.
    T& back() {
        if (_size == 0) throw std::logic_error("Vector is empty.");
        return _data[_size - 1];
    }
    // Const version.
    const T& back() const {
        if (_size == 0) throw std::logic_error("Vector is empty.");
        return _data[_size - 1];
    }
    #pragma endregion
};