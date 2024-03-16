#ifndef VECTOR_H
#define VECTOR_H

#include "Token.hpp"

class MyVector {
private:
    Token* elements;
    size_t size;
    size_t capacity; // New member to track capacity

public:
    MyVector() : size(0), elements(nullptr), capacity(0) {}

    ~MyVector() {
        delete[] elements;
    }

    MyVector(const MyVector& other) : size(other.size), capacity(other.capacity) {
        elements = new Token[capacity];
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    void push_back(const Token& element) {
        if (size == capacity) {
            size_t newCapacity = capacity == 0 ? 1 : capacity * 2; // Double the capacity
            Token* newElements = new Token[newCapacity];
            for (size_t i = 0; i < size; ++i) {
                newElements[i] = elements[i];
            }
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
        elements[size++] = element;
    }

    Token& operator[](size_t index) {
        return elements[index];
    }

    size_t getSize() const {
        return size;
    }
};

#endif
