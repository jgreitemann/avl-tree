#include "avl_tree.hpp"
#include <iostream>
#include <random>
#include <cassert>
#include <iterator>

using namespace std;

int main(int argc, char *argv[]) {
    avl_tree<double> t;
    const unsigned N = 100000;

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
        assert(*it == t[i]);
        assert(last <= *it);
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
                assert(*it == t[i]);
                assert(last <= *it);
                last = *it;
            }
        }

        d = (size_t)(t.size() * uniform(rng));
        it2 = t.begin();
        advance(it2, d);
        t.erase(it2);
    }

    return 0;
}
