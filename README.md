# avl-tree
A templated [AVL tree](https://en.wikipedia.org/wiki/AVL_tree) with STL-style iterators and random access; written in C++.

## Usage

The template parameter needs to be of a type supporting comparison operators `<`, `>`, `<=`, `>=`, `==`, and `!=`. While it is possible to obtain mutable references to elements in the tree via the `operator[]` and `find` member functions or by dereferencing mutable iterators, *it is crucial that any mutation of the tree's contents does not interfere with their relative ordering*.

The example below illustrates the basic use of the tree. A more complete documentation will hopefully be provided in the future. 

```c++
#include <iostream>
#include <avl_tree.hpp>

int main(int argc, char const *argv[]) {
    avl_tree<int> t;

    // insert elements to the tree
    t.insert(42);
    t.insert(17);
    t.insert(19);

    // iterate in order
    avl_tree<int>::const_iterator it;
    for (it = t.begin(); it != t.end(); ++it)
        std::cout << *it << ", ";
    std::cout << std::endl;

    // random-access elements by index
    std::cout << "Second smallest number: " << t[1] << std::endl;

    // remove element by value
    t.remove(19);

    return 0;
}
```


## Installation
Since the `avl_tree` is thoroughly templated, it lives entirely in the `avl_tree.hpp` header. You do not need to build it, before you can install it. Use

    $ make install

to copy the header to an include directory. The default install location is `/usr/local/include/`. To install e.g. to `~/.local/include/` instead, use

    $ PREFIX=$HOME/.local make install

(Note that the `include` directory is omitted in the prefix.)

### Running tests
This project uses Google's [libgtest](https://github.com/google/googletest) to run various tests. If you want to contribute to this project, make sure your modifications pass all the tests before submitting a pull request (or ask for help). Make sure gtests headers and the static library are in your compiler's include path and linker's library search path, respectively. Or, you can set the `$GTEST_INCLUDE_DIR` and `$GTEST_LIBS` environment variables.

    $ make test

will compile and run all the tests.
