//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_DYNAMICARRAY_H
#define LABA2_DYNAMICARRAY_H

#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class DynamicArray {
private:
    T *actual_array;
    size_t length;

public:
    //Creation of the object
    DynamicArray() : actual_array(new T[1]()), length(0) {}

    explicit DynamicArray(size_t count) {
        if (count < 0)
            throw out_of_range("count < 0");

        if (count > 0)
            actual_array = new T[count]();
        else
            actual_array = new T[1]();
        length = count;
    }

    DynamicArray(T *items, size_t count) {
        if (count < 0)
            throw out_of_range("count < 0");
        if (items == NULL)
            throw invalid_argument("items is NULL");
        if (count > 0) {
            actual_array = new T[count]();
            memcpy(actual_array, items, count * sizeof(T));
        } else {
            actual_array = new T[1]();
        }
        length = count;
    }

    DynamicArray(DynamicArray<T> const &dynamicArray) {
        length = dynamicArray.length;
        if (length > 0) {
            actual_array = new T[length]();
            memcpy(actual_array, dynamicArray.actual_array, length * sizeof(T));
        } else
            actual_array = new T[1]();
    }

    //Decomposition
    T &At(size_t index) {
        if (index < 0 || index >= length)
            throw out_of_range("index < 0 or index >= length");
        return actual_array[index];
    }

    void Set(size_t index, T value) {
        if (index < 0 || index >= length)
            throw range_error("index < 0 or index >= length");
        At(index) = value;
    }

    DynamicArray<T> GetSubArray(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= length)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= length)
            throw range_error("endIndex >= length");
        size_t len = endIndex - startIndex + 1;

        T arr[len];
        memcpy(arr, this->actual_array + startIndex, len * sizeof(T));
        return DynamicArray(arr, len);
    }

    size_t Count() { return length; }

    T &operator[](size_t index) { return At(index); }

    //Operations
    void Resize(size_t new_length) {
        if (new_length < 0) {
            throw range_error("new_length < 0");
        }
        T *new_array;

        if (new_length > 0) {
            new_array = new T[new_length]();
            size_t len = new_length > length ? length : new_length;
            memcpy(new_array, actual_array, sizeof(T) * len);
        } else new_array = new T[1]();
        delete[] actual_array;
        length = new_length;
        actual_array = new_array;
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &list) {
        this->~DynamicArray();
        length = list.length;
        if (length > 0) {
            actual_array = new T[length]();
            memcpy(actual_array, list.actual_array, length * sizeof(T));
        } else
            actual_array = new T[1]();
        return *this;
    }

    //Termination
    ~DynamicArray() { delete[] actual_array; }
};

#endif //LABA2_DYNAMICARRAY_H