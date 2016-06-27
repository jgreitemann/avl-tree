# avl-tree
A templated [AVL tree](https://en.wikipedia.org/wiki/AVL_tree) with STL-style iterators and random access; written in C++.

## Usage

The template parameter needs to be of a type that is default constructible as well as copy constructible and implements an ordering via `operator<` as well as the equality `operator==`. While it is possible to obtain mutable references to elements in the tree via the `operator[]` and `find` member functions or by dereferencing mutable iterators, *it is crucial that any mutation of the tree's contents does not interfere with their relative ordering*.

When storing compound data types in the tree, you may take advantage of move semantics by abiding to the *rule of five*. `insert` is overloaded to store rvalues.

The example below illustrates the basic use of the tree. A more complete documentation will hopefully be provided in the future. 

```c++
#include <iostream>
#include <avl_tree.hpp>

int main(int argc, char const *argv[]) {
    AVL::tree<int> t;

    // insert elements to the tree
    t.insert(42);
    t.insert(17);
    t.insert(19);

    // iterate in order
    AVL::tree<int>::const_iterator it;
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
This project uses CMake. To install, create a `build` directory, call `cmake` and `make install`:

    $ cd avl-tree
    $ mkdir build && cd build
    $ cmake ..
    $ make install

The default install location is `/usr/local/include/`. To install e.g. to `~/.local/include/` instead, use

    $ cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..

(Note that the `include` directory is omitted in the prefix.)

### Running tests
This project uses Google's [libgtest](https://github.com/google/googletest) to run various tests. If you want to contribute to this project, make sure your modifications pass all the tests before submitting a pull request (or ask for help). CMake will automatically clone the `googletest` repository in its build directory, configure and build it. To build and run the tests pertaining to `avl-tree`, run

    $ make test
