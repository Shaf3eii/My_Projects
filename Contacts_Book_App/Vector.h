//
// Created by Mahmoud Elshafei on 10/14/2024.
//

#ifndef CONTACTS_BOOK_APP_VECTOR_H
#define CONTACTS_BOOK_APP_VECTOR_H

#include <iostream>

template<typename T>
class Vector {
    size_t capacity{};
    size_t size{};
    T *arr{nullptr};

    void resize(size_t newCapacity) { // o(n) time - o(n) memory
        // Double the actual array size
        capacity = newCapacity;
        T *arr2 = new T[capacity]{};
        for (int i = 0; i < size; ++i)
            arr2[i] = arr[i]; // copy data
        std::swap(arr, arr2);
        delete[]arr2;
    }

public:
    // default constructor
    Vector() : size(0), capacity(1) { arr = new T[capacity]; }; // o(1) time - O(1) memory

    // parameterized constructor
    Vector(size_t size) : size(size), capacity(size + 10) { // o(n) time - O(n) memory
        arr = new T[capacity]{};
    }

    // parameterized constructor with default value initialization
    Vector(size_t size, T init_val) : size(size), capacity(size + 10) { // o(n) time - O(n) memory
        arr = new T[capacity]{};
        for (size_t i = 0; i < size; ++i)
            arr[i] = init_val;
    }

    // copy constructor
//    Vector(const Vector<T> &other) : size(other.size), capacity(other.capacity) { // o(n) time - o(n) memory
//        arr = new T[capacity];
//        std::copy(other, other + size, arr);
//    }

    // copy assignment operator
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete []arr;
            size = other.size;
            capacity = other.capacity;
            arr = new T[capacity];
            for (int i = 0; i < size; ++i) {
                arr[i] = other[i];
            }
        }
        return *this;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size)
            return false;

        for (size_t i = 0; i < size; ++i) {
            if (arr[i] != other.arr[i])
                return false;
        }
        return true;
    }
    bool operator!=(const Vector& other) const {
        return *this != other;
    }

    T &operator[](size_t idx) { // o(1) time - o(1) memory
        if (idx < 0 || idx >= size) // out of bounds
            throw std::out_of_range("Index out of range");
        return arr[idx];
    }

    const T &operator[](size_t idx) const {
        if (idx >= size) throw std::out_of_range("Index out of range");
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

    void PushFront(T val) { // O(n) time - o(1) memory
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

//        std::cout << "Deleted Element : " << arr[idx] << '\n';
        for (size_t i = idx; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        --size;
        if (size <= capacity / 4)
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
        delete[]arr;
        arr = nullptr;
    }

    void Resize(size_t newSize) { // O(n) time - o(1) memory
        size = newSize;
        capacity = size + 5;
        T *newArr = new T[capacity];
        copy(arr, arr + size, newArr);
        delete[] arr;
        arr = newArr;
    }

    // Static swap function
    void Swap(Vector &a, Vector &b) { // O(1) time - o(1) memory
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

    void reverse(int from = 0, int to = 0) { // o(n) time - o(1) memory
//        if(size == 0)
//            throw std::runtime_error("The Array is Empty..\n");

        if(!to)
            to = size - 1;
        for(int st = from , nd = to ; st < nd ; ++st , --nd) {
            T temp = arr[st];
            arr[st] = arr[nd];
            arr[nd] = temp;
        }
    }

    void sort() {
        if (size == 0)
            throw std::runtime_error("The Array is Empty..\n");
        // we can sort using different algorithms
        // I implemented 3 Algorithms and will explain the pros and cons of each one

        // bubble sort is an efficient algorithm with memory o(1) but it's time is o(n^2)
        // bubble sort is inefficient for large datasets.
        auto bubble_sort = [&]() {
            for (int i = 0; i < (size - 1); ++i) {
                for (int j = 0; j < (size - i - 1); ++j) {
                    if (arr[j] > arr[j + 1]) {
                        T temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        };
        bubble_sort();

//        // insertion sort is an efficient algorithm with memory o(1) but it's time is o(n^2)
//        // insertion sort is efficient for small datasets or nearly sorted arrays.
//        auto insertion_sort = [&]() {
//            for(int i = 0 ; i < (size - 1) ; ++i) {
//                for(int j = i + 1 ; j > 0 ; --j) {
//                    while(arr[j - 1] > arr[j]) {
//                        T temp = arr[j];
//                        arr[j] = arr[j - 1];
//                        arr[j - 1] = temp;
//                    }
//                }
//            }
//        };
//        insertion_sort();

//        // count sort is an efficient algorithm with time o(n) but it would using o(n) memory
//        // if the range of the elements is big, this algorithm wouldn't work efficiently
//        auto count_sort = [&](){
//            // Assuming T is int and values are in a small known range
//            if constexpr (std::is_integral<T>::value) {
//                int min_val = min_element();
//                int max_val = max_element();
//                std::vector<int> freq[max_val - min_val + 1];
//
//                int idx = 0;
//                for (int i = 0 ; i < (int)freq.size() ; ++i)
//                    while(freq[i]--)
//                        arr[idx++] = i + min_val;
//            }
//        };
//        count_sort();

//        o(nlogn) time
//        auto merge = [&](Vector<int>& vec, int left, int mid, int right) {
//            int i, j, k;
//            int n1 = mid - left + 1;
//            int n2 = right - mid;
//
//            // Create temporary vectors
//            Vector<int> leftVec(n1), rightVec(n2);
//
//            // Copy data to temporary vectors
//            for (i = 0; i < n1; i++)
//                leftVec[i] = vec[left + i];
//            for (j = 0; j < n2; j++)
//                rightVec[j] = vec[mid + 1 + j];
//
//            // Merge the temporary vectors back into vec[left..right]
//            i = 0;
//            j = 0;
//            k = left;
//            while (i < n1 && j < n2) {
//                if (leftVec[i] <= rightVec[j]) {
//                    vec[k] = leftVec[i];
//                    i++;
//                } else {
//                    vec[k] = rightVec[j];
//                    j++;
//                }
//                k++;
//            }
//            // Copy the remaining elements of leftVec[], if any
//            while (i < n1) {
//                vec[k] = leftVec[i];
//                i++;
//                k++;
//            }
//            // Copy the remaining elements of rightVec[], if any
//            while (j < n2) {
//                vec[k] = rightVec[j];
//                j++;
//                k++;
//            }
//        };
//        auto mergeSort = [&](auto& self,Vector<int>& vec, int left, int right)-> void {
//            if (left > right)
//                return;
//
//            // Calculate the midpoint
//            int mid = left + (right - left) / 2;
//
//            // Sort first and second halves
//            self(self,vec, left, mid);
//            self(self,vec, mid + 1, right);
//
//            // Merge the sorted halves
//            merge(vec, left, mid, right);
//        };
//        mergeSort(mergeSort, arr, 0, size - 1);
    }

    // destructor
    ~Vector() { // o(n) time - o(1) memory
        delete[]arr;
        arr = nullptr;
    }

    std::string getElements() {
        std::string elements = "";
        elements += arr[0];
        if(size > 1)
            elements += ", ..";
        return elements;
    }

    // print arr elements
    void print() const { // O(n) time - o(1) memory
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " \n"[i == size - 1];
    }
};

#endif //CONTACTS_BOOK_APP_VECTOR_H
