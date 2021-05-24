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
        items = BTree<T>();
    }

//    template<typename T1>
//    Set<T1> Map(T1 (*mapper)(T)) {
////        BTree<T1> *res;
////        auto res1 = BTree<T1>(res);
////        delete res;
////        return res1;
//    }
//
//    T Reduce(T (*func)(T, T)) {
//        Set<T> *res = dynamic_cast<Set<T1> *>(Enumerable<T>::template Map<T1, Set>(mapper));
//        auto res1 = Set<T1>(res);
//        delete res;
//        return res1;
//    }

    T Pop() {
        return items.Pop();
    }

    void Remove(T item) {
        items.Remove(item);
    }


    Set<T> Union(Set<T> const &list) {
        Set<T> res = Set<T>();
        Set<T> res1 = Set<T>(list);
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res.Add(items.At(i));
        }
        for (size_t i = 0; i < list.Count(); ++i) {
            res.Add(list[i]);
        }
        return res;
    }

    Set<T> Intersection(Set<T> const &list) {
//        stringstream buffer;
//        Stack<Pair<BNode *, size_t>> stack;
//        stack.Push(Pair(static_cast<BNode *>(this->root), (size_t) 0));
//        size_t length = this->count;
//        while (!stack.IsEmpty()) {
//
//            if (!stack.Top().first->IsLeaf()) {
//                if (stack.Top().first->ChildrenCount() == stack.Top().second)
//                    stack.Pop();
//                else {
//
//                    if (stack.Top().second != 0) {
//                        buffer << stack.Top().first->keys[stack.Top().second - 1];
//                        length--;
//                    }
//                    if (length != this->count && length)
//                        buffer << " ";
//                    stack.Push(Pair(stack.Top().first->GetChild(stack.Top().second++), (size_t) 0));
//                }
//            } else {
//                size_t len = stack.Top().first->keys.Count();
//                length -= len;
//                for (size_t i = 0; i < len; ++i) {
//                    buffer << stack.Top().first->keys[i];
//                    if (i != len - 1)
//                        buffer << " ";
//                }
//                stack.Pop();
//            }
//        }
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

    friend ostream &operator<<(ostream &out, const Set<T> &x) {
        ArraySequence<T> tmp = x.ToArraySequence();
        out << "{";
        size_t length = tmp.Count();
        for (size_t i = 0; i < length; ++i) {
            out << tmp[i];
            if (i != length - 1)
                out << ", ";
        }
        out << "}" << endl;
        return out;
    }

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

    bool operator==(const Set<T> &x) const { return !(*this != x); }

    bool operator!=(const Set<T> &x) const {
        return abs(this->real - x.real) >= numeric_limits<float>::epsilon() ||
               abs(this->imaginary - x.imaginary) >= numeric_limits<float>::epsilon();
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
