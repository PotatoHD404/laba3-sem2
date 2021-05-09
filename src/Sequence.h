//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "Enumerable.h"
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Sequence : public Enumerable<T> {
public:
    Sequence() = default;

    //Decomposition
    T &GetFirst() { return At(0); }

    T &GetLast() { return At(this->Count() - 1); }

    void Set(size_t index, T value) {
        At(index) = value;
    }

    virtual T &At(size_t index) = 0;

//    virtual size_t Count() = 0;

    T &operator[](size_t index) { return At(index); }

    //Operations
    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(size_t index, T item) = 0;

    virtual T PopFirst() = 0;

    virtual T PopLast() = 0;

    virtual T RemoveAt(size_t index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> &list) = 0;

    virtual Sequence<T> *Concat(const unique_ptr<Sequence<T>> &list) {
        return Concat(*list);
    }

    virtual ~Sequence() = default;
};

#endif //LABA2_SEQUENCE_H