//
// Created by korna on 03.04.2021.
//


#ifndef LABA2_IENUMERABLE_H
#define LABA2_IENUMERABLE_H

#include "IEnumerator.h"
#include "ICollection.h"

template<typename T>
class IEnumerable {
protected:
    class Enumerator : public IEnumerator<T> {
    private:
        ICollection<T> *items;
        size_t pos;

    public:
        explicit Enumerator(ICollection<T> *arr) {
            items = arr;
            pos = 0;
        }

        T &GetCurrent() {
            return items->At(pos);
        }

        size_t GetLength() {
            return items->GetLength();
        }

        bool MoveNext() {
            if (++pos < items->GetLength())
                return true;
            pos--;
            return false;
        }

        void Reset() {
            pos = 0;
        }
    };

public:

    virtual IEnumerator<T> *GetEnumerator() = 0;
};

#endif //LABA2_IENUMERABLE_H