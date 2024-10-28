//
// Created by Mahmoud Elshafei on 10/14/2024.
//

#include <iostream>

template <typename T>
class Vector {
    size_t capacity { };
    size_t size { };
    T *arr {nullptr};

    void resize(size_t newCapacity) { // o(n) time - o(n) memory
        // Double the actual array size
        capacity = newCapacity;
        T *arr2 = new T [capacity] { };
        for(int i = 0 ; i < size ; ++i)
            arr2[i] = arr[i]; // copy data
        std::swap(arr, arr2);
        delete []arr2;
    }

public:
    // default constructor
    Vector() : size(0), capacity(1) { arr = new T [capacity]; }; // o(1) time - O(1) memory

    // parameterized constructor
    Vector(size_t size) : size(size), capacity(size + 10) { // o(n) time - O(n) memory
        arr = new T [capacity] { };
    }

    // parameterized constructor with default value initialization
    Vector(size_t size, T init_val) : size(size), capacity(size + 10) { // o(n) time - O(n) memory
        arr = new T [capacity] { };
        for(size_t i = 0 ; i < size ; ++i)
            arr[i] = init_val;
    }

    // copy constructor
    Vector(Vector& other) : size(other.size) , capacity(other.capacity) { // o(n) time - o(n) memory
        arr = new T[capacity];
        copy(other, other + size, arr);
    }

    // copy assignment operator
    Vector& operator=(Vector& other) { // o(n) time - o(1) memory
        std::swap(other);
        return *this;
    }

    T& operator[](size_t idx) { // o(1) time - o(1) memory
        if (idx < 0 || idx >= size) // out of bounds
            throw std::out_of_range("Index out of range");
        return arr[idx];
    }

    // Accessor methods
    size_t getSize() const { // o(1) time - o(1) memory
        return size;
    }

    size_t getCapacity() const { // o(1) time - o(1) memory
        return capacity;
    }

    size_t get(size_t idx) const { // o(1) time - o(1) memory
        if (idx < 0 || idx >= size) // out of bounds
            throw std::out_of_range("Index out of range");
        return arr[idx];
    }

    T front() const { // o(1) time - o(1) memory
        if (!size)
            throw std::out_of_range("Vector is empty");
        return arr[0];
    }

    T back() const { // o(1) time - o(1) memory
        if (!size)
            throw std::out_of_range("Vector is empty");
        return arr[size - 1];
    }

    // Modification methods
    void PushBack(T val) { // O(1) time - o(1) memory
        if (size == capacity)
            resize(capacity * 2);
        arr[size++] = val;
    }

    void PushFront(int val) { // O(n) time - o(1) memory

        if (size == capacity)
            resize(capacity * 2);
        for (int i = size; i > 0; --i)
            arr[i] = arr[i - 1];
        arr[0] = val;
        ++size;
    }

    T PopBack() { // O(1) time - o(1) memory
        if (size > 0)
            return arr[--size];
    }

    void insert(size_t idx, T val) { // O(n) time - o(1) memory
        if (idx < 0 || idx > size) // out of bounds
            throw std::out_of_range("Index out of range");

        if (size == capacity)
            resize(capacity * 2);

        for (int i = size; i > idx; --i)
            arr[i] = arr[i - 1];
        arr[idx] = val;
        ++size;
    }

    void remove(size_t idx) { // O(n) time - o(1) memory

        if (idx < 0 || idx >= size) // out of bounds
            throw std::out_of_range("Index out of range");

        std::cout << "Deleted Element : " << arr[idx] << '\n';
        for (size_t i = idx; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        --size;
        if(size <= capacity / 4)
            resize(capacity / 2);
    }

    void set(size_t idx, T val) { // O(1) time - o(1) memory
        if (idx < 0 || idx >= size) // out of bounds
            throw std::out_of_range("Index out of range");

        arr[idx] = val;
    }

    void clear() { // O(1) time - o(1) memory !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        size = 0;
        capacity = 1;
        delete []arr;
        arr = nullptr;
    }

    void Resize(size_t newSize) { // O(n) time - o(1) memory

        size = newSize;
        capacity = size + 5;
        T* newArr = new T[capacity];
        copy(arr, arr + size, newArr);
        delete[] arr;
        arr = newArr;
    }

    // Static swap function
    void Swap(Vector& a, Vector& b) { // O(1) time - o(1) memory
        a.swap(b);
    }

    // Utility methods
    bool isEmpty() const { // O(1) time - o(1) memory
        return size == 0;
    }

    size_t find(T val) const { // O(n) time - o(1) memory
        for (int i = 0; i < size; ++i) {
            if (arr[i] == val)
                return i;
        }
        return -1; // not found
    }

    // destructor
    ~Vector() { // o(n) time - o(1) memory
        delete []arr;
        arr = nullptr;
    }

    // print arr elements
    void print() const { // O(n) time - o(1) memory
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " \n"[i == size - 1];
    }
};