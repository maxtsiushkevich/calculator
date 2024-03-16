#ifndef VECTOR_H
#define VECTOR_H

class MyVector {
private:
    Token* elements;
    size_t size;
    size_t capacity;

public:
    MyVector() : size(0), capacity(0), elements(nullptr) {}

    ~MyVector() {
        clear();
        operator delete(elements);
    }

    MyVector(const MyVector& other) : size(other.size), capacity(other.capacity + 1) {
        elements = new Token[other.capacity + 1];
        copyElements(other.elements, other.size, elements);
    }

    void push_back(const Token& element) {
        if (size >= capacity)
            reserve(capacity + 1);
        elements[size++] = Token(element);
    }

    Token& operator[](size_t index) {
        return elements[index];
    }

    size_t getSize() const {
        return size;
    }

private:
    void reserve(size_t newCapacity) {
        Token* newElements = static_cast<Token*>(operator new(newCapacity * sizeof(Token)));
        copyElements(elements, size, newElements);
        delete elements;
        elements = newElements;
        capacity = newCapacity;
    }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            elements[i].~Token();
        }
        size = 0;
    }

    void copyElements(const Token* source, size_t count, Token* dest) {
        for (size_t i = 0; i < count; ++i) {
            dest[i] = source[i];
        }
    }
};

#endif