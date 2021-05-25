//
// Created by korna on 17.05.2021.
//

#ifndef LABA3_SET_H
#define LABA3_SET_H

#include "BTree.hpp"
#include "Sequence.hpp"

template<typename T>
class Set {
private:
    BTree<T> items;

public:
    //Creation of the object
    Set() : items() {}

    Set(T *items, size_t count) : items(items, count) {
    }

    Set(initializer_list<T> const &items) : Set() {
        for (T item : items)
            this->Add(item);
    }

    Set(Set<T> &list) : items(list.items) {}

    explicit Set(const Set<T> *list) : Set(*list) {}

    //Decomposition

    Set<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        Set<T> *res = new Set<T>();
        res->items = items.GetSubList(startIndex, endIndex);
        return res;
    }

    size_t Count() {
        return items.Count();
    }

    //Operations
    void Clear() {
        items = BTree<T>();
    }

    template<typename T1>
    Set<T1> Map(T1 (*mapper)(T)) {
        Set<T1> res;
        static_cast<NAryTree<T> &>(res.items) = items.Map(mapper);
        ArraySequence<T> x = res.items.ToArraySequence();
        res.items = BTree<T>();
        for (size_t i = 0; i < x.Count(); ++i)
            res.Add(x[i]);

        return res;
    }

    T Reduce(T (*func)(T, T), T x) {
        return items.Reduce(func, x);
    }

    T Pop() {
        return items.Pop();
    }

    void Add(T item) {
        items.Insert(item);
    }

    bool Contains(T item) {
        return items.Contains(item);
    }

    void Remove(T item) {
        return items.Remove(item);
    }

    Set<T> Union(Set<T> &list) {
        Set<T> res = Set<T>(*this);
        ArraySequence<T> arr = list.items.ToArraySequence();
        for (size_t i = 0; i < arr.Count(); ++i) {
            res.Add(arr[i]);
        }
        return res;
    }

    string AsTree() {
        return items.Order();
    }

    Set<T> Intersection(Set<T> &list) {
        Set<T> res = Set<T>();
        ArraySequence<T> arr1 = items.ToArraySequence();
        ArraySequence<T> arr2 = list.items.ToArraySequence();
        size_t i = 0, j = 0;
        while (true) {
            if (arr1[i] == arr2[j]) {
                res.Add(arr1[i]);
                i++;
                j++;
            } else if (arr1[i] < arr2[j]) {
                if (i == arr1.Count() - 1)
                    break;
                i++;
            } else if (arr1[i] > arr2[j]) {
                if (j == arr2.Count() - 1)
                    break;
                j++;
            }
        }
        return res;
    }

    Set<T> Difference(Set<T> &list) {
        Set<T> res = Set<T>(*this);
        ArraySequence<T> arr = list.items.ToArraySequence();
        for (size_t i = 0; i < arr.Count(); ++i) {
            res.Remove(arr[i]);
        }
        return res;
    }

    friend ostream &operator<<(ostream &out, Set<T> &x) {
        ArraySequence<T> tmp = x.items.ToArraySequence();
        out << "{";
        size_t length = tmp.Count();
        for (size_t i = 0; i < length; ++i) {
            out << tmp[i];
            if (i != length - 1)
                out << ", ";
        }
        out << "}";
        return out;
    }

    ArraySequence<T> ToArraySequence() {
        return items.ToArraySequence();
    }

    friend ostream &operator<<(ostream &out, Set<T> &&x) { return operator<<(out, x); }

    friend istream &operator>>(istream &in, Set<T> &x) {
        string tmp;
        getline(in, tmp);
        stringstream ss(tmp);
        T t;
        while (ss >> t) {
            x.Add(t);
        }
        return in;
    }
//    bool operator==(Set<T> &x) { return x.items == this->items; }
//    bool operator==(Set<T> &&x) { return x.items == this->items; }

    bool operator==(Set<T> &list) {
        return list.items.ToArraySequence() == items.ToArraySequence();
    }

    bool operator==(Set<T> &&list) {
        return list.items.ToArraySequence() == items.ToArraySequence();
    }

    bool operator!=(const Set<T> &x) const {
        return x.items != this->items;
    }

    Set<T> &operator+=(const Set<T> &list) {
        *this = *this + list;
        return *this;
    }

    Set<T> &operator*=(const Set<T> &list) {
        *this = *this * *list;
        return *this;
    }

    Set<T> &operator-=(const Set<T> &list) {
        *this = *this - list;
        return *this;
    }

    Set<T> operator+(Set<T> &list) {
        return Union(list);
    }

    Set<T> operator*(Set<T> &list) {
        return Intersection(list);
    }

    Set<T> operator-(Set<T> &list) {
        return Difference(list);
    }
};

#endif //LABA3_SET_H
