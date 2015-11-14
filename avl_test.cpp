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
    //t.remove(6);
    cout << t << endl;
    t.insert(14);
    cout << t << endl;
    t2 = t;
    t.insert(12);
    cout << t << endl;
    //t.remove(1);
    //cout << t << endl;
    //t2.remove(8);
    //cout << t2 << endl;

    t.clear();
    t2.clear();
    cout << t << endl;

    return 0;
}
