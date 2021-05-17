//
// Created by korna on 03.04.2021.
//
#ifndef LABA2_ENUMERABLE_H
#define LABA2_ENUMERABLE_H

#include "ICollection.h"
#include <vector>
#include <tuple>
#include <iostream>
//#include <variant>

using namespace std;

template<typename T>
/*abstract*/
class Enumerable : public ICollection<T> {
private:
    template<typename Base, typename T1>
    inline constexpr static bool instanceof(const T1 *) {
        return is_base_of<Base, T1>::value;
    }

    template<typename ElType, template<typename> class Child>
    static constexpr bool IsBadType(Child<ElType> *x) {
        return !instanceof<ICollection<ElType>>(x);
    }

    template<typename... Args, typename... Ts, template<typename> class Current, typename ElType>
    static auto Zip(vector<tuple<Ts...>> &res, size_t min, Current<ElType> current, Args... args) {
        if constexpr (static_cast<ICollection<ElType> *>(&current) == nullptr)
            throw std::runtime_error("Wrong type");
        else {
            size_t count = current.Count();
            vector<tuple<Ts..., ElType>> res2;
            if (min > count)
                min = count;
            for (size_t i = 0; i < min; i++)
                res2.push_back(tuple_cat(res.at(i), make_tuple(current[i])));
            if constexpr (sizeof...(Args) == 0) {
                res2.resize(min);
                return res2;
            } else
                return Zip(res2, min, args...);
        }
    }

    template<template<typename> typename ChildClass, size_t num, class Current, typename... Ts, typename... Args, typename... Ts1>
    static auto UnZip(vector<tuple<Ts1...>> &input, Args... args) {
        size_t length = input.size();
        auto res = ChildClass<Current>();
        for (size_t i = 0; i < length; i++)
            res.Append(get<num>(input.at(i)));

        if constexpr (sizeof...(Ts) == 0)
            return make_tuple(args..., res);
        else
            return UnZip<ChildClass, num + 1, Ts...>(input, args..., res);
    }

protected:
    template<typename T1, template<typename> class ChildClass>
    Enumerable<T1> *Map(T1 (*mapper)(T)) {
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        size_t length = this->Count();
        Enumerable<T1> *res = new ChildClass<T1>(length);
        for (size_t i = 0; i < length; i++)
            res->At(i) = mapper(this->At(i));
        return res;
    }

    template<template<typename> class ChildClass>
    Enumerable<T> *Where(bool(*predicate)(T)) {
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Enumerable<T> *res = new ChildClass<T>();
        for (size_t i = 0; i < this->Count(); i++)
            if (predicate(this->At(i)))
                res->Append(this->At(i));
        return res;
    }

public:

    auto Split(size_t pos) {
        auto res = make_tuple(this->Subsequence(0, pos), this->Subsequence(pos + 1, this->Count() - 1));
        return res;
    }

    bool Contains(T item) {
        for (size_t i = 0; i < this->Count(); ++i)
            if (this->At(i) == item)
                return true;
        return false;
    }

    virtual Enumerable<T> *Subsequence(size_t begin, size_t end) = 0;

    T Reduce(T(*f)(T, T), T const c) {
        if (f == nullptr)
            throw std::invalid_argument("mapper is NULL");
        T res = c;
        for (size_t i = 0; i < this->Count(); ++i) {
            res = f(this->At(i), res);
        }
        return res;
    }


    template<typename... Args, template<typename> class Current, typename ElType>
    static auto Zip(Current<ElType> current, Args... args) {
        if constexpr(IsBadType(&current))
            throw std::runtime_error("Wrong type");
        else {
            const size_t count = current.Count();
            vector<tuple<ElType>> res;
            for (size_t i = 0; i < count; i++)
                res.push_back(make_tuple(current[i]));

            return Zip(res, count, args...);
        }
    }

    template<template<typename> typename ChildClass, typename... Args, typename Current, typename... Ts>
    static auto UnZip(vector<tuple<Current, Ts...>> input, Args... args) {
        size_t length = input.size();
        if (length == 0)
            throw std::runtime_error("Wrong size of input vector");
        auto res = ChildClass<Current>();
        for (size_t i = 0; i < length; i++)
            res.Append(get<0>(input.at(i)));

        if constexpr (sizeof...(Ts) == 0)
            return make_tuple(res, args...);
        else
            return UnZip<ChildClass, 1, Ts...>(input, args..., res);
    }

    virtual ~Enumerable() = default;
};


#endif //LABA2_ENUMERABLE_H