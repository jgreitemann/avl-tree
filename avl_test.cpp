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

#define DEBUGMODE
#include "avl_tree.hpp"
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, char *argv[]) {
    avl_tree<int> t, t2;
    int nums[] = {17, 6, 8, 7, 13, 1, 16};
    for (int i = 0; i < 7; ++i) {
        t.insert(nums[i]);
        cout << t << endl;
    }
    t.insert(14);
    cout << "inserted 14:" << endl << t << endl;
    t2 = t;
    t.insert(12);
    cout << "inserted 12 in t:" << endl << t << endl;

    cout << "Testing iterator: ";
    avl_tree<int>::const_iterator it;
    for (it = t.begin(); it != t.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Testing random access: ";
    for (size_t i = 0; i < t.size(); i++) {
        cout << t[i] << " ";
    }
    cout << endl;

    it = t.find(7);
    cout << "Finding element 7: " << *it << endl;

    t.remove(1);
    cout << "removed 1 from t:" << endl << t << endl;
    t2.remove(8);
    cout << "removed 8 from t2:" << endl << t2 << endl;
    t2.remove(16);
    cout << "removed 16 from t2:" << endl << t2 << endl;

    t.clear();
    t2.clear();
    cout << t << endl;

    return 0;
}
