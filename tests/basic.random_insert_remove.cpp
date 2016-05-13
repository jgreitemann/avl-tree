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

TEST(basic, random_insert_remove) {
    avl_tree<double> t;
    const unsigned N = 10000;

    random_double_fill(t, N);

    // check ordering and consistent indices/iterators
    avl_tree<double>::const_iterator it;
    double last = 0.;
    size_t i;
    for (it = t.begin(), i = 0; it != t.end(); ++it, ++i) {
        ASSERT_EQ(*it, t[i]);
        ASSERT_EQ(true, last <= *it);
        last = *it;
    }

    // randomly pick elements and delete
    mt19937 rng;
    uniform_real_distribution<double> uniform;
    avl_tree<double>::iterator it2;
    size_t d;
    for (size_t i = 0; i < N; i++) {
        // check again half-way in
        if (i == N/2) {
            last = 0.;
            for (it = t.begin(), i = 0; it != t.end(); it++, ++i) {
                ASSERT_EQ(*it, t[i]);
                ASSERT_EQ(true, last <= *it);
                last = *it;
            }
        }

        d = (size_t)(t.size() * uniform(rng));
        it2 = t.at(d);
        t.erase(it2);
    }
    ASSERT_EQ(0, t.size());
}
