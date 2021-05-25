//
// Created by korna on 18.05.2021.
//

#include "gtest/gtest.h"
#include "../Set.hpp"
#include <string>

using namespace std;

int mapper1(int a) {
    return a * 2;
}

string mapper2(string a) {
    return a + " sampleText";
}

int ReduceCheck(int a, int b) {
    return a + b;
}

TEST(SetTest, Init) {
    Set<int> set = Set<int>();
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Add(4);

    Set<int> set1 = Set<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(set == set1);
}

TEST(SetTest, Add_Remove) {
    Set<int> set = Set<int>();
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Remove(0);
    set.Remove(3);
    ASSERT_TRUE(set.Contains(2));
    ASSERT_FALSE(set.Contains(3));

    Set<int> set1 = Set<int>({1, 2});
    ASSERT_TRUE(set1 == set);
    set.Remove(1);
    set.Remove(2);
    EXPECT_EQ(set.Count(),0);
    ASSERT_TRUE(set == Set<int>());

}

TEST(SetTest, Map) {
    Set<int> set = Set<int>({4, 3, 2, 0});
    Set<int> mapSet = set.Map(mapper1);
    ASSERT_TRUE(mapSet == Set<int>({8, 6, 4, 0}));

    Set<string> setString = Set<string>({"", "0"});
    Set<string> mapSetString = setString.Map(mapper2);
    ASSERT_TRUE(mapSetString == Set<string>({" sampleText", "0 sampleText"}));
}

TEST(SetTest, Reduce) {
    Set<int> set = Set<int>({2, 3, 4, 0});
    int reduce = set.Reduce(ReduceCheck, 0);
    ASSERT_EQ(reduce, 9);
}

TEST(SetTest, Inersection) {
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    Set<int> intersection = set * set1;
    ASSERT_TRUE(intersection == Set<int>({4, 5}));
}

TEST(SetTest, Union) {
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    Set<int> uni = set + set1;
    ASSERT_TRUE(uni == Set<int>({1, 2, 3, 4, 5, 6, 7, 8}));
}

TEST(SetTest, Substraction) {
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    Set<int> sub = set - set1;
    ASSERT_TRUE(sub == Set<int>({1, 2, 3}));
}

TEST(SetTest, EqualTest) {
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>(set);
    ASSERT_TRUE(set1 == set);
}