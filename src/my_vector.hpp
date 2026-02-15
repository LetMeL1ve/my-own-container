#pragma once
#include <cstddef>

template <typename T>
class MyVector {
private:
    T* _data;  // Dynamic array which stores all of the values.

    size_t _size;  // Current size of vector.
    size_t _capacity;  // Number of elements which are memory reserved for.
public:
    // Constructors and destructor.
    MyVector();  // Default constructor.
    MyVector(size_t);  // Constructor with size.
    MyVector(const MyVector&);  // Copy constructor.
    MyVector(MyVector&&);  // Move constructor.

    ~MyVector();
    
    // Getters.
    inline T* data() const { return _data; }
    inline size_t capacity() const { return _capacity; }
    inline size_t size() const { return _size; }
};