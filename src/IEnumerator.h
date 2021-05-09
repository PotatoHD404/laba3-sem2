//
// Created by korna on 03.04.2021.
//

#ifndef LABA2_IENUMERATOR_H
#define LABA2_IENUMERATOR_H

template<typename T>
class IEnumerator {
public:
    virtual T &GetCurrent() = 0;

    virtual bool MoveNext() = 0;

    virtual void Reset() = 0;

    virtual size_t GetLength() = 0;

    virtual ~IEnumerator() = default;
};

#endif //LABA2_IENUMERATOR_H