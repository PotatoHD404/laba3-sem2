//
// Created by korna on 17.05.2021.
//

#ifndef LABA3_SET_H
#define LABA3_SET_H

#include "BTree.hpp"
#include "Sequence.hpp"

//template<typename T>
//class Set : public Sequence<T> {
//private:
//    
//public:
//    Set() {}
//
//};

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

    Set(Set<T> const &list) : items(list.items) {}

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
        return items.GetLength();
    }

    bool operator==(Set<T> const &list) {
        return list.items == items;
    }

    //Operations
    void Clear() {
        items = Set<T>();
    }

    template<typename T1>
    Set<T1> Map(T1 (*mapper)(T)) {
        Set<T1> *res;
        auto res1 = Set<T1>(res);
        delete res;
        return res1;
    }

    T Reduce(T (*func)(T, T)) {
        Set<T> *res = dynamic_cast<Set<T1> *>(Enumerable<T>::template Map<T1, Set>(mapper));
        auto res1 = Set<T1>(res);
        delete res;
        return res1;
    }

    T Pop() {
        return items.Pop();
    }

    void Remove(T item) {
        items.Remove(item);
    }


    Set<T> Union(Set<T> const &list1, Set<T> const &list2) {
        Set<T> *res = new Set<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items.At(i));
        }
        for (size_t i = 0; i < list.Count(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    Set<T> Intersection(Set<T> const &list) {
        Set<T> *res = new Set<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items.At(i));
        }
        for (size_t i = 0; i < list.Count(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    Set<T> Difference(Set<T> const &list) {
        Set<T> *res = new Set<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items.At(i));
        }
        for (size_t i = 0; i < list.Count(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    friend ostream &operator<<(ostream &out, const Sequence<T> &x) {
//        out << TypeName<ChildClass<T>>() << "(";
        out << "{";
        size_t length = x.Count();
        for (size_t i = 0; i < length; ++i) {
            out << x[i];
            if (i != length - 1)
                out << ", ";
        }
        out << "}" << endl;
//        out << ")" << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Sequence<T> &x) {
        string tmp;
        getline(in, tmp);
        stringstream ss(tmp);
        T t;
        while (ss >> t) {
            x.Append(t);
        }
        return in;
    }

    bool operator==(const Set<T> &x) const { return !(*this != x); }

    bool operator!=(const Set<T> &x) const {
        if (abs(this->real - x.real) >= numeric_limits<float>::epsilon() ||
            abs(this->imaginary - x.imaginary) >= numeric_limits<float>::epsilon())
            return true;
        else
            return false;
    }

    Set<T> &operator+=(const Set<T> &list) {
        *this = this * +list;
        return *this;
    }

    Set<T> &operator*=(const Set<T> &list) {
        *this = this * *list;
        return *this;
    }

    Set<T> &operator-=(const Set<T> &list) {
        *this = this * -list;
        return *this;
    }

    Set<T> operator+(const Set<T> &list) {
        items = LinkedList<T>(list.items);
        return *this;
    }

    Set<T> operator*(const Set<T> &list) {
        items = LinkedList<T>(list.items);
        return *this;
    }

    Set<T> operator-(const Set<T> &list) {
        items = LinkedList<T>(list.items);
        return *this;
    }
};

#endif //LABA3_SET_H
