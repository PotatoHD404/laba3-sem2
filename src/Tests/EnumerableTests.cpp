//
// Created by korna on 19.04.2021.
//


#include "gtest/gtest.h"
#include <iostream>
#include "../Enumerable.hpp"
#include "../ListSequence.hpp"
#include "../ArraySequence.hpp"

using namespace std;

TEST(Enumerable, ListSequence_Zip) {
    ArraySequence<int> a = {0, 1, 2};
    ArraySequence<int> b = {3, 2};
    auto res = ArraySequence<int>::Zip(a, b);
    auto[x1, x2] = res[0];
    EXPECT_EQ(x1, 0);
    EXPECT_EQ(x2, 3);
    auto[x3, x4] = res[1];
    EXPECT_EQ(x3, 1);
    EXPECT_EQ(x4, 2);
    EXPECT_EQ(res.size(), 2);

    ArraySequence<float> c = {3.14, 2.1};
    auto res1 = ArraySequence<int>::Zip(a, c);
    auto[x5, x6] = res1[0];
    EXPECT_EQ(x5, 0);
    EXPECT_FLOAT_EQ(x6, 3.14);
    auto[x7, x8] = res1[1];
    EXPECT_EQ(x7, 1);
    EXPECT_FLOAT_EQ(x8, 2.1);
    EXPECT_EQ(res1.size(), 2);


    ArraySequence<float> d = {};
    res1 = ArraySequence<int>::Zip(a, d);
    EXPECT_EQ(res1.size(), 0);
    vector<int> tmp;
    EXPECT_ANY_THROW(ArraySequence<int>::Zip(tmp, d));
}

TEST(Enumerable, ListSequence_UnZip) {
    ArraySequence<int> a = {0, 1, 2};
    ArraySequence<int> b = {3, 2};
    vector<tuple<int, int>> input = ArraySequence<int>::Zip(a, b);
    auto[x1, x2] = ArraySequence<int>::UnZip<ArraySequence>(input);
    EXPECT_FALSE(x1 == a);
    EXPECT_EQ(x1[0], a[0]);
    EXPECT_EQ(x1[1], a[1]);
    EXPECT_TRUE(x2 == b);

    vector<tuple<int, int>> badInput;
    EXPECT_ANY_THROW(ArraySequence<int>::UnZip<ArraySequence>(badInput));

    a = {0, 1, 2};
    ArraySequence<float> c = {4.15, 2.2};
    vector<tuple<int, float>> input1 = ArraySequence<int>::Zip(a, c);
    auto[x3, x4] = ArraySequence<int>::UnZip<ArraySequence>(input1);
    EXPECT_FALSE(x3 == a);
    EXPECT_EQ(x3[0], a[0]);
    EXPECT_EQ(x3[1], a[1]);

    EXPECT_TRUE(x4 == c);
    vector<tuple<int, float>> badInput1;
    EXPECT_ANY_THROW(ArraySequence<int>::UnZip<ArraySequence>(badInput1));
}

int Pow(int x) {
    return x * x;
}

bool IsEven(int x) {
    return x % 2 == 0;
}


TEST(Enumerable, ListSequence_Map) {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    ListSequence<int> res = arr.Map(Pow);
    EXPECT_TRUE(res == ListSequence<int>({121, 144, 9, 16, 25}));
    ListSequence<int> res1 = ListSequence<int>({}).Map(Pow);
    EXPECT_TRUE(res1 == ListSequence<int>({}));
    ListSequence<bool> res2 = ListSequence<int>({11, 12, 3, 4, 6}).Map(IsEven);
    EXPECT_TRUE(res2 == ListSequence<bool>({false, true, false, true, true}));
    int (*wrong)(int) = nullptr;
    EXPECT_ANY_THROW(arr.Map(wrong));
}

int f(int x, int y) {
    return x + y;
}

TEST(Enumerable, ListSequence_Reduce) {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    EXPECT_EQ(arr.Reduce(f, 0), 25);
    int res2 = ListSequence<int>({}).Reduce(f, -1);
    EXPECT_EQ(res2, -1);
    int (*wrong)(int, int) = nullptr;
    EXPECT_ANY_THROW(arr.Reduce(wrong, 0));
}

TEST(Enumerable, ListSequence_Where) {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    EXPECT_TRUE(arr.Where(IsEven) == ListSequence<int>({12, 4}));
    ListSequence<int> res2 = ListSequence<int>({}).Where(IsEven);
    EXPECT_TRUE(res2 == ListSequence<int>());
    bool (*wrong)(int) = nullptr;
    EXPECT_ANY_THROW(arr.Where(wrong));
}

TEST(Enumerable, ListSequence_Contains) {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    EXPECT_TRUE(arr.Contains(11));
    EXPECT_TRUE(arr.Contains(12));
    EXPECT_TRUE(arr.Contains(-5));
    EXPECT_FALSE(arr.Contains(7));
    arr = {};
    EXPECT_FALSE(arr.Contains(-5));
}

TEST(Enumerable, ListSequence_Split) {
    ListSequence<int> arr = {11, 12, 3, 4, -5};
    auto[a, b] = arr.Split(0);
    EXPECT_TRUE(*dynamic_cast<ListSequence<int> *>(a) == ListSequence<int>({11}));
    EXPECT_TRUE(*dynamic_cast<ListSequence<int> *>(b) == ListSequence<int>({12, 3, 4, -5}));
    delete a;
    delete b;
}