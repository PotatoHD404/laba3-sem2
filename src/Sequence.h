//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "Enumerable.h"
#include <iostream>
#include <memory>

using namespace std;

template<class T>
class Sequence : public Enumerable<T> {
public:
    Sequence() {}

    //Decomposition
    T &GetFirst() { return At(0); }

    T &GetLast() { return At(this->GetLength() - 1); }

    void Set(size_t index, T value) {
        At(index) = value;
    }

    virtual T &At(size_t index) = 0;

//    virtual size_t GetLength() = 0;

    T &operator[](size_t index) { return At(index); }

    //Operations
    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, size_t index) = 0;

    virtual void PopFirst() = 0;

    virtual void PopLast() = 0;

    virtual void RemoveAt(size_t index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> &list) = 0;

    virtual Sequence<T> *Concat(const unique_ptr<Sequence<T>> &list) {
        return Concat(*list);
    }

    virtual ~Sequence() {};
};

#endif //LABA2_SEQUENCE_H