//
// Created by korna on 05.05.2021.
//

#ifndef LABA3_STACK_HPP
#define LABA3_STACK_HPP

#include "ListSequence.hpp"

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
        return this->Count() == 0;
    }

};

#endif //LABA3_STACK_HPP
