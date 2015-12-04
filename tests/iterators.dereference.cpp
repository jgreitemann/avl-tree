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
