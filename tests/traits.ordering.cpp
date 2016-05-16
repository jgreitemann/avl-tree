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
#include "../avl_traits.hpp"
#include <type_traits>
#include <complex>

const size_t N = 100;

class data_t {
    private:
        double *payload;
        double sum() const {
            double s = 0;
            for (size_t i = 0; i < N; ++i)
                s += payload[i];
            return s;
        }
    public:
        data_t() {
            payload = new double[N];
            for (size_t i = 0; i < N; ++i)
                payload[i] = 0.;
        }
        data_t(const data_t& d) {
            payload = new double[N];
            for (size_t i = 0; i < N; ++i)
                payload[i] = d.payload[i];
        }
        ~data_t() {
            delete[] payload;
        }
        bool operator<(const data_t& d) const {
            return sum() < d.sum();
        }
        bool operator==(const data_t& d) const {
            bool res = true;
            for (size_t i = 0; i < N; ++i)
                res &= (payload[i] == d.payload[i]);
            return res;
        }
};

class dumb_data_t {};


TEST(traits, ordering) {
    ASSERT_TRUE(AVL::defines_ordering<data_t>::value);
    ASSERT_TRUE(AVL::defines_ordering<double>::value);
    ASSERT_FALSE(AVL::defines_ordering<dumb_data_t>::value);
    ASSERT_FALSE(AVL::defines_ordering<std::complex<double>>::value);
}
