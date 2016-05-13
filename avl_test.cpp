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

#include "avl_test.hpp"

void random_double_fill(avl_tree<double> &t, const unsigned N) {
    mt19937 rng;
    uniform_real_distribution<double> uniform;

    // fill with random numbers
    size_t i;
    for (i = 0; i < N; i++) {
        t.insert(uniform(rng));
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
