//
// Created by korna on 05.05.2021.
//

#ifndef LABA3_STACK_H
#define LABA3_STACK_H

#include "ListSequence.h"

template<class T>
class Stack : ListSequence<T> {
public:
    Stack() = default;

    void Push(T item) {
        this->Prepend(item);
    }

    T Pop() {
        return this->PopFirst();
    }

    bool IsEmpty() {
        return this->GetLength() == 0;
    }

};

#endif //LABA3_STACK_H
