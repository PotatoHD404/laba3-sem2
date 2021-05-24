//
// Created by korna on 18.05.2021.
//

#include "gtest/gtest.h"

#include "../Complex.hpp"
#include "../NAryTree.hpp"
#include "../Person.hpp"
#include "../BTree.hpp"
#include "../Set.hpp"

TEST(NAryTree_int, InitDefault) {
    NAryTree<int> tree(4);
    EXPECT_ANY_THROW(arr.GetFirst());
    EXPECT_ANY_THROW(arr.GetLast());
}