//    avl-tree
//    Copyright (C) 2015 -- 2016  Jonas Greitemann
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

TEST(tree, swap) {
    AVL::tree<double> t, s;
    const unsigned N = 10000;
    random_double_fill(t, N);
    random_double_fill(s, 2*N);

    // copy first
    AVL::tree<double> t2(t);
    AVL::tree<double> s2(s);

    ASSERT_TRUE(t2 == t);
    ASSERT_FALSE(t2 == s);

    t2.swap(s2);
    ASSERT_FALSE(t2 == t);
    ASSERT_TRUE(t2 == s);

    swap(s2, t2);
    ASSERT_TRUE(t2 == t);
    ASSERT_FALSE(t2 == s);
}
