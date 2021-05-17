//
// Created by korna on 17.04.2021.
//

#ifndef TEST_DB_DYNAMICARRAYTESTS_H
#define TEST_DB_DYNAMICARRAYTESTS_H

#include "gtest/gtest.h"
#include "../DynamicArray.h"

TEST(DynamicArray, InitDefault_Set_Resize) {
    DynamicArray<int> arr = DynamicArray<int>();
    ASSERT_EQ (0, arr.Count());
    EXPECT_ANY_THROW(arr.Resize(-1));
    arr.Resize(1);
    ASSERT_EQ (1, arr.Count());
    EXPECT_ANY_THROW(arr.At(-1));
    EXPECT_ANY_THROW(arr.At(1));

    arr.At(0) = 5;
    EXPECT_EQ (5, arr.At(0));
    EXPECT_ANY_THROW(arr.Set(-1, 1));
    EXPECT_ANY_THROW(arr.Set(1, 1));

    arr.Set(0, 1);
    EXPECT_EQ (1, arr.At(0));
}

TEST(DynamicArray, InitCount) {
    EXPECT_ANY_THROW(DynamicArray<int>(-1));
    DynamicArray<int> arr = DynamicArray<int>(2);
    ASSERT_EQ (2, arr.Count());
    arr.At(0) = 1;
    EXPECT_EQ (1, arr.At(0));
    EXPECT_EQ (0, arr.At(1));

    arr = DynamicArray<int>(0);
    ASSERT_EQ (0, arr.Count());
}

TEST(DynamicArray, InitFromArr) {
    int a[] = {1, 2, 3, 4, 5};
    EXPECT_ANY_THROW(DynamicArray<int>(a, -1));
    EXPECT_ANY_THROW(DynamicArray<int>(nullptr, 1));
    DynamicArray<int> arr = DynamicArray<int>(a, 5);
    ASSERT_EQ (5, arr.Count());
    arr.Resize(6);
    ASSERT_EQ (6, arr.Count());

    arr[5] = 6;
    EXPECT_EQ (1, arr.At(0));
    EXPECT_EQ (2, arr.At(1));
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);
    EXPECT_EQ (6, arr[5]);

    arr.Resize(5);
    EXPECT_ANY_THROW(arr.At(5));
    ASSERT_EQ (5, arr.Count());
    arr.Set(0, 0);
    EXPECT_EQ (1, a[0]);
    EXPECT_EQ (0, arr.At(0));
    EXPECT_EQ (2, arr.At(1));
    EXPECT_EQ (3, arr[2]);
    EXPECT_EQ (4, arr[3]);
    EXPECT_EQ (5, arr[4]);

    arr = DynamicArray<int>(a, 0);
    ASSERT_EQ (0, arr.Count());
}

TEST(DynamicArray, InitFromDynamicArray) {
    int a[] = {1, 2, 3, 4, 5, 6};
    DynamicArray<int> arr1 = DynamicArray<int>(a, 5);
    ASSERT_EQ (5, arr1.Count());
    EXPECT_ANY_THROW(arr1.At(5));
    DynamicArray<int> arr2 = DynamicArray<int>(arr1);
    ASSERT_EQ (5, arr2.Count());
    EXPECT_EQ (arr1.At(0), arr2.At(0));
    EXPECT_EQ (arr1.At(1), arr2.At(1));
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr1.Set(0, 2);
    EXPECT_EQ (arr1.At(0), 2);
    EXPECT_EQ (arr2.At(0), 1);
    arr2.Resize(arr2.Count() + 1);
    ASSERT_EQ (5, arr1.Count());
    ASSERT_EQ (6, arr2.Count());

    arr1 = DynamicArray<int>();
    arr2 = DynamicArray<int>(arr1);
    ASSERT_EQ (0, arr2.Count());
}

TEST(DynamicArray, GetSubArray) {
    int a[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr1 = DynamicArray<int>(a, 5);
    DynamicArray<int> arr2 = arr1.GetSubArray(0, 0);
    ASSERT_EQ(arr2.Count(), 1);
    EXPECT_EQ (arr1.At(0), 1);
    EXPECT_ANY_THROW(arr2.At(1));
    EXPECT_ANY_THROW(arr1.GetSubArray(-1, 0));
    EXPECT_ANY_THROW(arr1.GetSubArray(1, 0));
    EXPECT_ANY_THROW(arr1.GetSubArray(1, 5));

    arr2 = arr1.GetSubArray(0, 4);
    ASSERT_EQ(arr2.Count(), 5);
    EXPECT_EQ (arr1.At(0), arr2.At(0));
    EXPECT_EQ (arr1.At(1), arr2.At(1));
    EXPECT_EQ (arr1[2], arr2[2]);
    EXPECT_EQ (arr1[3], arr2[3]);
    EXPECT_EQ (arr1[4], arr2[4]);

    arr2 = arr1.GetSubArray(2, 3);
    ASSERT_EQ(arr2.Count(), 2);
    EXPECT_EQ (arr1[2], arr2.At(0));
    EXPECT_EQ (arr1[3], arr2.At(1));
}


#endif //TEST_DB_DYNAMICARRAYTESTS_H