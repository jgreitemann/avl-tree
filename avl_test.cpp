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

mt19937 rng;
uniform_real_distribution<double> uniform;

void random_double_fill(avl_tree<double> &t, const unsigned N) {
    // fill with random numbers
    size_t i;
    for (i = 0; i < N; i++) {
        t.insert(uniform(rng));
    }
}

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
                ASSERT_EQ(true, *it1 == *it2);
                ASSERT_EQ(false, it1 != it2);
                ASSERT_EQ(false, passed);
                passed = true;
                ASSERT_EQ(false, it1 < it2);
                ASSERT_EQ(false, it1 > it2);
                ASSERT_EQ(true, it1 <= it2);
                ASSERT_EQ(true, it1 >= it2);
            } else {
                ASSERT_EQ(false, *it1 == *it2);
                ASSERT_EQ(true, it1 != it2);
                if (passed) {
                    ASSERT_EQ(false, it1 < it2);
                    ASSERT_EQ(false, it1 <= it2);
                    ASSERT_EQ(true,  it1 > it2);
                    ASSERT_EQ(true,  it1 >= it2);
                } else {
                    ASSERT_EQ(true, it1 < it2);
                    ASSERT_EQ(true, it1 <= it2);
                    ASSERT_EQ(false,  it1 > it2);
                    ASSERT_EQ(false,  it1 >= it2);
                }
            }
        }
    }
}

TEST(iterators, dereference) {
    avl_tree<double> t;
    const unsigned N = 1000;
    random_double_fill(t, N);

    struct wrapper {
        double data;
        wrapper() {};
        wrapper(const double d) : data(d) {};
        bool operator<(const wrapper &o) const { return data < o.data; }
        bool operator>(const wrapper &o) const { return data > o.data; }
        bool operator<=(const wrapper &o) const { return data <= o.data; }
        bool operator>=(const wrapper &o) const { return data >= o.data; }
        bool operator==(const wrapper &o) const { return data == o.data; }
        bool operator!=(const wrapper &o) const { return data != o.data; }
    };

    avl_tree<wrapper> w;
    avl_tree<double>::const_iterator it;
    for (it = t.cbegin(); it != t.cend(); ++it) {
        w.insert(wrapper(*it));
    }
    avl_tree<wrapper>::const_iterator wit;
    for (it = t.cbegin(), wit = w.cbegin(); it != t.cend(); ++it, ++wit) {
        ASSERT_EQ(*it, wit->data);
    }
    ASSERT_EQ(wit, w.cend());
}

TEST(tree, equality) {
    avl_tree<double> t, s;
    const unsigned N = 1000;
    random_double_fill(t, N);

    avl_tree<double>::const_iterator it;
    for (it = t.cbegin(); it != t.cend(); ++it) {
        s.insert(*it);
    }

    ASSERT_EQ(s, t);
    ASSERT_EQ(t, s);
    ASSERT_EQ(false, s != t);
    ASSERT_EQ(false, t != s);

    int r = (int)(t.size() * uniform(rng));
    s.erase(s.at(r));
    ASSERT_EQ(true, s != t);
    ASSERT_EQ(true, t != s);
    ASSERT_EQ(false, s == t);
    ASSERT_EQ(false, t == s);
}

TEST(tree, copy) {
    avl_tree<double> t;
    const unsigned N = 10000;
    random_double_fill(t, N);

    avl_tree<double> s(t);
    ASSERT_EQ(t, s);

    int r = (int)(s.size() * uniform(rng));
    s.erase(s.at(r));
    ASSERT_EQ(true, t != s);
}

TEST(tree, copy_assign) {
    avl_tree<double> t;
    const unsigned N = 10000;
    random_double_fill(t, N);

    avl_tree<double> s = t;
    ASSERT_EQ(t, s);

    int r = (int)(s.size() * uniform(rng));
    s.erase(s.at(r));
    ASSERT_EQ(true, t != s);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
