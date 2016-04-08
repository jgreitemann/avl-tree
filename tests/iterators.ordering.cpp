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

TEST(iterators, ordering) {
    avl_tree<double> t;
    const unsigned N = 100;
    random_double_fill(t, N);
    avl_tree<double>::iterator iit1;
    avl_tree<double>::const_iterator it2;
    for (iit1 = t.begin(); iit1 != t.end(); ++iit1) {
        bool passed = false;
        avl_tree<double>::const_iterator it1(iit1);
        for (it2 = --t.end(); it2 != t.begin(); it2--) {
            if (it1 == it2) {
                ASSERT_TRUE(*it1 == *it2);
                ASSERT_FALSE(it1 != it2);
                ASSERT_FALSE(passed);
                passed = true;
                ASSERT_FALSE(it1 < it2);
                ASSERT_FALSE(it1 > it2);
                ASSERT_TRUE(it1 <= it2);
                ASSERT_TRUE(it1 >= it2);
            } else {
                ASSERT_FALSE(*it1 == *it2);
                ASSERT_TRUE(it1 != it2);
                if (passed) {
                    ASSERT_FALSE(it1 < it2);
                    ASSERT_FALSE(it1 <= it2);
                    ASSERT_TRUE(it1 > it2);
                    ASSERT_TRUE(it1 >= it2);
                } else {
                    ASSERT_TRUE(it1 < it2);
                    ASSERT_TRUE(it1 <= it2);
                    ASSERT_FALSE(it1 > it2);
                    ASSERT_FALSE(it1 >= it2);
                }
            }
        }
    }
}
