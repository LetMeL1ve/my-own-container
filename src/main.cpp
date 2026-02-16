#include <iostream>
#include <string>
#include "my_vector.hpp"

struct TestObject {
    std::string name;

    TestObject() : name("default") {
        std::cout << "Default constructor\n";
    }

    TestObject(const std::string& n) : name(n) {
        std::cout << "Custom constructor\n";
    }

    TestObject(const TestObject& other) : name(other.name) {
        std::cout << "Copy constructor\n";
    }

    TestObject(TestObject&& other) noexcept : name(std::move(other.name)) {
        std::cout << "Move constructor\n";
    }

    ~TestObject() {
        std::cout << "Destructor for: " << name << "\n";
    }
};

int main() {
    
}