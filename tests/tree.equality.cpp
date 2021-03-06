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

TEST(tree, equality) {
    AVL::tree<double> t, s;
    const unsigned N = 1000;
    random_double_fill(t, N);

    AVL::tree<double>::const_iterator it;
    for (it = t.cbegin(); it != t.cend(); ++it) {
        s.insert(*it);
    }

    ASSERT_EQ(s, t);
    ASSERT_EQ(t, s);
    ASSERT_FALSE(s != t);
    ASSERT_FALSE(t != s);

    mt19937 rng;
    uniform_real_distribution<double> uniform;
    int r = (int)(t.size() * uniform(rng));
    s.erase(s.at(r));
    ASSERT_TRUE(s != t);
    ASSERT_TRUE(t != s);
    ASSERT_FALSE(s == t);
    ASSERT_FALSE(t == s);
}
