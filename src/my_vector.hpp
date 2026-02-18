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
    MyVector(size_t size) : _size(size) {
        if (size == 0)
            _capacity = 1;

        _data = new T[_capacity] {};
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

    #pragma region Vector change functions

    //  Sets ```_size``` to 0.
    void clear() noexcept { _size = 0;}

    // Changes the ```_capacity``` to ```new_capacity```. If ```new_capacity``` is equal or smaller than current does nothing.
    // Can throw std::exception if there is a problem with element copying.
    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity)
            return;  // Exit if new capacity is equal or smaller.

        T* new_data = new T[new_capacity];

        try {
            if constexpr (std::is_nothrow_move_assignable_v<T>
                          || !std::is_copy_assignable_v<T>) {
                for (size_t i = 0; i < _size; ++i) 
                    new_data[i] = std::move(_data[i]);
            } else {
                for (size_t i = 0; i < _size; ++i) 
                    new_data[i] = _data[i]; 
            }
        } catch (...) {
            delete[] new_data;  // Deleting memory if there is an error of element copying.
            throw;
        }

        delete[] _data;  // Free old memory.
        _data = new_data;  // Moving to the pointer of resized array.

        _capacity = new_capacity;  // Updating the capacity.
    }

    // Resizes vector to ```new_size```. If ```new_size``` is bigger than current capacity, doubles capacity.
    void resize(size_t new_size) {
        // ```new_size < _capacity``` case: Simply decreasing _size and quiting.
        if (new_size <= _capacity) {
            _size = new_size;
            return;
        }

        // Increasing ```_capacity```.
        while (new_size > _capacity)
            reserve(_capacity * 2);
        
        _size = new_size;
    };

    // Adds an element to the end of container.
    void push_back(const T& obj) {
        if ((_size + 1) > _capacity)
            reserve(_capacity * 2);

        _data[_size] = obj;

        ++_size;
    }
    // rvalue overload of ```push_back```.
    void push_back(T&& obj) {
        if ((_size + 1) > _capacity)
            reserve(_capacity * 2);

        _data[_size] = std::move(obj);

        ++_size;
    }

    // Deletes last element of vector. if vector is empty throws and std::logic_error.
    void pop_back() {
        if (_size == 0)
            throw std::logic_error("Vector is empty.");
        --_size;
    }

    #pragma endregion
};