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

#include "avl_tree.hpp"
#include <random>
#include <gtest/gtest.h>

using namespace std;

TEST(avl_tree, random_test) {
    avl_tree<double> t;
    const unsigned N = 1000000;

    mt19937 rng;
    uniform_real_distribution<double> uniform;

    // fill with random numbers
    size_t i;
    for (i = 0; i < N; i++) {
        t.insert(uniform(rng));
    }

    // check ordering and consistent indices/iterators
    avl_tree<double>::const_iterator it;
    double last = 0.;
    for (it = t.begin(), i = 0; it != t.end(); ++it, ++i) {
        ASSERT_EQ(*it, t[i]);
        ASSERT_EQ(true, last <= *it);
        last = *it;
    }

    // randomly pick elements and delete
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
