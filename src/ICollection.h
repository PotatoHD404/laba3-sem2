//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_ICOLLECTION_H
#define LABA2_ICOLLECTION_H

template<typename T>
class ICollection {
public:
    ICollection() = default;

    //Decomposition

    virtual T &At(size_t index) = 0;

    virtual size_t GetLength() = 0;

    virtual bool Contains(T item) = 0;

    //Operations
    virtual void Clear() = 0;

    virtual void Append(T item) = 0;

    virtual T RemoveAt(size_t index) = 0;

    virtual ~ICollection() = default;
};

#endif //LABA2_ICOLLECTION_H