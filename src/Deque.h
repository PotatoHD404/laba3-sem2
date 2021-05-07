//
// Created by korna on 05.05.2021.
//

#ifndef LABA3_DEQUE_H
#define LABA3_DEQUE_H

#include "ListSequence.h"

template<class T>
class Deque : ListSequence<T> {
public:
    Deque() = default;

    void Push(T item) {
        this->Prepend(item);
    }

    void PushBack(T item) {
        this->Append(item);
    }

    T Pop() {
        return this->PopFirst();
    }

    bool IsEmpty() {
        return this->GetLength() == 0;
    }

};

#endif //LABA3_DEQUE_H
