//
// Created by korna on 17.04.2021.
//

#ifndef TEST_DB_ARRAYSEQUENCETESTS_H
#define TEST_DB_ARRAYSEQUENCETESTS_H

#include "gtest/gtest.h"
#include "../ArraySequence.hpp"

TEST(ArraySequence_int, InitDefault) {
    ArraySequence<int> arr = ArraySequence<int>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW(arr.GetLast());
}

TEST(ArraySequence_int, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ArraySequence<int>(-1));
    ArraySequence<int> arr = ArraySequence<int>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (0, arr.GetLast());
    arr = ArraySequence<int>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ArraySequence<int>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ArraySequence_int, Append) {
    ArraySequence<int> arr = ArraySequence<int>();
    arr.Append(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.At(-1));
    EXPECT_ANY_THROW(arr.At(1));
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Append(5);
    ASSERT_EQ (2, arr.Count());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.Append(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());
}

TEST(ArraySequence_int, Prepend) {
    ArraySequence<int> arr = ArraySequence<int>();
    arr.Prepend(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.At(-1));
    EXPECT_ANY_THROW(arr.At(1));
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Prepend(5);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());

    arr.Prepend(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
}

TEST(ArraySequence_int, InsertAt) {
    ArraySequence<int> arr = ArraySequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.InsertAt(1, 4);
    ASSERT_EQ (4, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (2, arr[2]);
    EXPECT_EQ (3, arr[3]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.InsertAt(0, 5);
    ASSERT_EQ (5, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.InsertAt(arr.Count() - 1, 6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (6, arr[5]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (6, arr.GetLast());
}

TEST(ArraySequence_int, PopFirst) {
    ArraySequence<int> arr = ArraySequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.PopFirst();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (2, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (2, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.PopFirst();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.PopFirst();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW (arr.PopFirst(););
}

TEST(ArraySequence_int, PopLast) {
    ArraySequence<int> arr = ArraySequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.PopLast();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (2, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
}

TEST(ArraySequence_int, RemoveAt) {
    ArraySequence<int> arr = ArraySequence<int>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr.At(2));
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ArraySequence<int>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ArraySequence_int, InitFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ArraySequence<int>(a, -1));
    EXPECT_ANY_THROW(ArraySequence<int>(nullptr, 1));
    ArraySequence<int> arr = ArraySequence<int>(a, 5);
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.PopLast();
    EXPECT_ANY_THROW(arr.At(5));
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    arr = ArraySequence<int>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ArraySequence<int>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ArraySequence<int>({1, 2, 3, 4, 5});
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);
}

TEST(ArraySequence_int, InitFromArraySequence) {
    int a[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1.At(5));
    ArraySequence<int> arr2 = ArraySequence<int>(arr1);
    ASSERT_EQ (5, arr2.Count());
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1[0], 2);
    EXPECT_EQ (arr2[0], 1);
    arr2.Append(0);
    ASSERT_EQ (5, arr1.Count());
    ASSERT_EQ (6, arr2.Count());

    arr1 = ArraySequence<int>();
    arr2 = ArraySequence<int>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

TEST(ArraySequence_int, Concat) {
    int a[] = {1, 2, 3, 4, 5};
    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
    ArraySequence<int> arr2 = ArraySequence<int>(arr1);
    std::unique_ptr<ArraySequence<int>> arr3 = std::unique_ptr<ArraySequence<int>>(arr1.Concat(arr2));
    ASSERT_EQ (arr1.Count() + arr2.Count(), arr3->Count());
    EXPECT_EQ (arr1[0], arr3->At(0));
    EXPECT_EQ (arr1[1], arr3->At(1));
    EXPECT_EQ (arr1[2], arr3->At(2));
    EXPECT_EQ (arr1[3], arr3->At(3));
    EXPECT_EQ (arr1[4], arr3->At(4));
    EXPECT_EQ (arr2[0], arr3->At(5));
    EXPECT_EQ (arr2[1], arr3->At(6));
    EXPECT_EQ (arr2[2], arr3->At(7));
    EXPECT_EQ (arr2[3], arr3->At(8));
    EXPECT_EQ (arr2[4], arr3->At(9));

    ArraySequence<int> arr4 = ArraySequence<int>();
    arr3 = std::unique_ptr<ArraySequence<int>>(arr1.Concat(arr4));
    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
    EXPECT_EQ (arr1[0], arr3->At(0));
    EXPECT_EQ (arr1[1], arr3->At(1));
    EXPECT_EQ (arr1[2], arr3->At(2));
    EXPECT_EQ (arr1[3], arr3->At(3));
    EXPECT_EQ (arr1[4], arr3->At(4));
}

TEST(ArraySequence_int, GetSubsequence) {
    int a[] = {1, 2, 3, 4, 5};
    ArraySequence<int> arr1 = ArraySequence<int>(a, 5);
    unique_ptr<ArraySequence<int>>
            arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(0, 0));
    ASSERT_EQ(arr2->Count(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr2->At(1));
    EXPECT_ANY_THROW(arr1.GetSubsequence(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 5));
    arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(0, 4));
    ASSERT_EQ(arr2->Count(), 5);
    EXPECT_EQ (arr1[0], arr2->At(0));
    EXPECT_EQ (arr1[1], arr2->At(1));
    EXPECT_EQ (arr1[2], arr2->At(2));
    EXPECT_EQ (arr1[3], arr2->At(3));
    EXPECT_EQ (arr1[4], arr2->At(4));
    arr2 = unique_ptr<ArraySequence<int>>(arr1.GetSubsequence(2, 3));
    ASSERT_EQ(arr2->Count(), 2);
    EXPECT_EQ (arr1[2], arr2->At(0));
    EXPECT_EQ (arr1[3], arr2->At(1));
}

TEST(ArraySequence_float, InitDefault) {
    ArraySequence<float> arr = ArraySequence<float>();
    ASSERT_EQ(0, arr.Count());
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW(arr.GetLast());
}

TEST(ArraySequence_float, InitCount_Set_Clear) {
    EXPECT_ANY_THROW(ArraySequence<float>(-1));
    ArraySequence<float> arr = ArraySequence<float>(2);
    ASSERT_EQ (2, arr.Count());
    arr[0] = 1;
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (0, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (0, arr.GetLast());
    arr = ArraySequence<float>(0);
    ASSERT_EQ (0, arr.Count());
    arr = ArraySequence<float>(10);
    ASSERT_EQ (10, arr.Count());
    arr.Clear();
    EXPECT_EQ (0, arr.Count());
}


TEST(ArraySequence_float, Append) {
    ArraySequence<float> arr = ArraySequence<float>();
    arr.Append(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.At(-1));
    EXPECT_ANY_THROW(arr.At(1));
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Append(5);
    ASSERT_EQ (2, arr.Count());
    arr.Set(0, 1);
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (5, arr.GetLast());

    arr.Append(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());
}

TEST(ArraySequence_float, Prepend) {
    ArraySequence<float> arr = ArraySequence<float>();
    arr.Prepend(5);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.At(-1));
    EXPECT_ANY_THROW(arr.At(1));
    EXPECT_EQ (5, arr[0]);

    arr[0] = 4;
    EXPECT_EQ (4, arr[0]);
    EXPECT_EQ (4, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Prepend(5);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());

    arr.Prepend(3);
    ASSERT_EQ (3, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (5, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (4, arr.GetLast());
}

TEST(ArraySequence_float, InsertAt) {
    ArraySequence<float> arr = ArraySequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.InsertAt(1, 4);
    ASSERT_EQ (4, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (4, arr[1]);
    EXPECT_EQ (2, arr[2]);
    EXPECT_EQ (3, arr[3]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.InsertAt(0, 5);
    ASSERT_EQ (5, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.InsertAt(arr.Count() - 1, 6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (5, arr[0]);
    EXPECT_EQ (1, arr[1]);
    EXPECT_EQ (4, arr[2]);
    EXPECT_EQ (2, arr[3]);
    EXPECT_EQ (3, arr[4]);
    EXPECT_EQ (6, arr[5]);
    EXPECT_EQ (5, arr.GetFirst());
    EXPECT_EQ (6, arr.GetLast());
}

TEST(ArraySequence_float, PopFirst) {
    ArraySequence<float> arr = ArraySequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.PopFirst();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (2, arr[0]);
    EXPECT_EQ (3, arr[1]);
    EXPECT_EQ (2, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.PopFirst();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.PopFirst();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW (arr.PopFirst(););
}

TEST(ArraySequence_float, PopLast) {
    ArraySequence<float> arr = ArraySequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr.PopLast();
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (2, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.PopLast();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
}

TEST(ArraySequence_float, RemoveAt) {
    ArraySequence<float> arr = ArraySequence<float>(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    ASSERT_ANY_THROW(arr.RemoveAt(-1));
    ASSERT_ANY_THROW(arr.RemoveAt(3));
    arr.RemoveAt(1);
    ASSERT_EQ (2, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (3, arr[1]);
    ASSERT_ANY_THROW (arr.At(2));
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (3, arr[0]);
    EXPECT_EQ (3, arr.GetFirst());
    EXPECT_EQ (3, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));

    arr = ArraySequence<float>(2);
    arr[0] = 1;
    arr[1] = 2;

    arr.RemoveAt(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (1, arr.GetFirst());
    EXPECT_EQ (1, arr.GetLast());

    arr.RemoveAt(0);
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW (arr.At(0));
    EXPECT_ANY_THROW (arr.GetFirst());
    EXPECT_ANY_THROW (arr.GetLast());
    EXPECT_ANY_THROW(arr.PopLast());
    EXPECT_ANY_THROW(arr.RemoveAt(0));
}

TEST(ArraySequence_float, InitFromArr) {
    float a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(ArraySequence<float>(a, -1));
    EXPECT_ANY_THROW(ArraySequence<float>(nullptr, 1));
    ArraySequence<float> arr = ArraySequence<float>(a, 5);
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.PopLast();
    EXPECT_ANY_THROW(arr.At(5));
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    arr = ArraySequence<float>(a, 0);
    ASSERT_EQ (0, arr.Count());

    arr = ArraySequence<float>(a);
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = ArraySequence<float>({1, 2, 3, 4, 5});
    ASSERT_EQ (5, arr.Count());

    arr.Append(6);
    ASSERT_EQ (6, arr.Count());
    EXPECT_EQ (1, arr[0]);
    EXPECT_EQ (2, arr[1]);
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr = {};
    ASSERT_EQ (0, arr.Count());
    arr.Append(6);
    ASSERT_EQ (1, arr.Count());
    EXPECT_EQ (6, arr[0]);
    EXPECT_ANY_THROW(arr.At(1));
}

TEST(ArraySequence_float, InitFromArraySequence) {
    float a[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1.At(5));
    ArraySequence<float> arr2 = ArraySequence<float>(arr1);
    ASSERT_EQ (5, arr2.Count());
    EXPECT_EQ (arr1[0], arr2[0]);
    EXPECT_EQ (arr1[1], arr2[1]);
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1[0], 2);
    EXPECT_EQ (arr2[0], 1);
    arr2.Append(0);
    ASSERT_EQ (5, arr1.Count());
    ASSERT_EQ (6, arr2.Count());

    arr1 = ArraySequence<float>();
    arr2 = ArraySequence<float>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

TEST(ArraySequence_float, Concat) {
    float a[] = {1, 2, 3, 4, 5};
    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
    ArraySequence<float> arr2 = ArraySequence<float>(arr1);
    std::unique_ptr<ArraySequence<float>> arr3 = std::unique_ptr<ArraySequence<float>>(arr1.Concat(arr2));
    ASSERT_EQ (arr1.Count() + arr2.Count(), arr3->Count());
    EXPECT_EQ (arr1[0], arr3->At(0));
    EXPECT_EQ (arr1[1], arr3->At(1));
    EXPECT_EQ (arr1[2], arr3->At(2));
    EXPECT_EQ (arr1[3], arr3->At(3));
    EXPECT_EQ (arr1[4], arr3->At(4));
    EXPECT_EQ (arr2[0], arr3->At(5));
    EXPECT_EQ (arr2[1], arr3->At(6));
    EXPECT_EQ (arr2[2], arr3->At(7));
    EXPECT_EQ (arr2[3], arr3->At(8));
    EXPECT_EQ (arr2[4], arr3->At(9));

    ArraySequence<float> arr4 = ArraySequence<float>();
    arr3 = std::unique_ptr<ArraySequence<float>>(arr1.Concat(arr4));
    ASSERT_EQ (arr1.Count() + arr4.Count(), arr3->Count());
    EXPECT_EQ (arr1[0], arr3->At(0));
    EXPECT_EQ (arr1[1], arr3->At(1));
    EXPECT_EQ (arr1[2], arr3->At(2));
    EXPECT_EQ (arr1[3], arr3->At(3));
    EXPECT_EQ (arr1[4], arr3->At(4));
}

TEST(ArraySequence_float, GetSubsequence) {
    float a[] = {1, 2, 3, 4, 5};
    ArraySequence<float> arr1 = ArraySequence<float>(a, 5);
    unique_ptr<ArraySequence<float>>
            arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(0, 0));
    ASSERT_EQ(arr2->Count(), 1);
    EXPECT_EQ (arr1[0], 1);
    EXPECT_ANY_THROW(arr2->At(1));
    EXPECT_ANY_THROW(arr1.GetSubsequence(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubsequence(1, 5));
    arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(0, 4));
    ASSERT_EQ(arr2->Count(), 5);
    EXPECT_EQ (arr1[0], arr2->At(0));
    EXPECT_EQ (arr1[1], arr2->At(1));
    EXPECT_EQ (arr1[2], arr2->At(2));
    EXPECT_EQ (arr1[3], arr2->At(3));
    EXPECT_EQ (arr1[4], arr2->At(4));
    arr2 = unique_ptr<ArraySequence<float>>(arr1.GetSubsequence(2, 3));
    ASSERT_EQ(arr2->Count(), 2);
    EXPECT_EQ (arr1[2], arr2->At(0));
    EXPECT_EQ (arr1[3], arr2->At(1));
}



TEST(ArraySequence_int, Equals) {
    ArraySequence<int> arr{1, 2, 3};
    ArraySequence<int> arr1{1, 2};
    ArraySequence<int> arr2{1, 2, 3};
    ArraySequence<int> arr3{3, 2};
    EXPECT_TRUE(arr == arr2);
    EXPECT_FALSE(arr == arr1);
    EXPECT_FALSE(arr1 == arr3);
    ArraySequence<int> arr4{};
    ArraySequence<int> arr5{};
    EXPECT_TRUE(arr4 == arr5);
}


#endif //TEST_DB_ARRAYSEQUENCETESTS_H