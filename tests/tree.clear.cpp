//    avl-tree
//    Copyright (C) 2015  Jonas Greitemann
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

#include "../avl_test.hpp"

TEST(tree, clear) {
    avl_tree<double> t;
    const unsigned N = 10000;

    random_double_fill(t, N);
    ASSERT_FALSE(t.empty());
    ASSERT_EQ(N, t.size());

    t.clear();
    ASSERT_TRUE(t.empty());
    ASSERT_EQ(0, t.size());

    random_double_fill(t, N);
    ASSERT_FALSE(t.empty());
    ASSERT_EQ(N, t.size());
}
