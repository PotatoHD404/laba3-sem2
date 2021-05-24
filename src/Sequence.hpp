//
// Created by korna on 20.03.2021.
//
#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H

#include "Enumerable.hpp"
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class Sequence : public Enumerable<T> {
private:
//    template<typename T1>
//    static string TypeName() {
//        typedef typename remove_reference<T1>::type TR;
//        unique_ptr<char, void (*)(void *)> own(nullptr, free);
//        std::string r = own != nullptr ? own.get() : typeid(TR).name();
//        if (std::is_const<TR>::value)
//            r += " const";
//        if (std::is_volatile<TR>::value)
//            r += " volatile";
//        if (std::is_lvalue_reference<T>::value)
//            r += "&";
//        else if (std::is_rvalue_reference<T>::value)
//            r += "&&";
//        return r;
//    }

public:
    Sequence() = default;

    //Decomposition
    T &GetFirst() { return At(0); }

    T &GetLast() { return At(this->Count() - 1); }

    void Set(size_t index, T value) {
        At(index) = value;
    }

    virtual T &At(size_t index) = 0;

    virtual T &operator[](size_t index) = 0;

    friend ostream &operator<<(ostream &out, Sequence<T> &&x) {
//        out << TypeName<ChildClass<T>>() << "(";
        out << "[";
        size_t length = x.Count();
        for (size_t i = 0; i < length; ++i) {
            out << x[i];
            if (i != length - 1)
                out << ", ";
        }
        out << "]";
//        out << ")" << endl;
        return out;
    }
//    friend ostream &operator<<(ostream &out,const Sequence<T> &x){return operator<<(out, &x); }
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