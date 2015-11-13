#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <memory>
#include <iterator>
#include <exception>
#include <stdexcept>

template <typename T, typename A = std::allocator<T> >
class avl_tree {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

private:
    class node {
    public:
        T data;
        avl_tree *tree;
        short imbalance;
        size_type n;
        node *parent;
        node *left_child;
        node *right_child;

        node(avl_tree& tree) : tree(&tree) {
            imbalance = 0;
            n = 1;
            parent = 0;
            left_child = 0;
            right_child = 0;
        }
        node(avl_tree& tree, const node& nd) : tree(&tree) {
            left_child = 0;
            right_child = 0;
            *this = nd;
        }
        node(avl_tree& tree, const T& t) : tree(&tree) {
            data = t;
            imbalance = 0;
            n = 1;
            left_child = 0;
            right_child = 0;
        }
        ~node() {
            if (left_child) {
                tree->alloc.destroy(left_child);
                tree->alloc.deallocate(left_child, 1);
            }
            if (right_child) {
                tree->alloc.destroy(right_child);
                tree->alloc.deallocate(right_child, 1);
            }
        }

        node& operator=(const node& nd) {
            data = nd.data;
            imbalance = nd.imbalance;
            n = nd.n;
            if (left_child) {
                if (nd.left_child) {
                    *left_child = *nd.left_child;
                    left_child->parent = this;
                } else {
                    tree->alloc.destroy(left_child);
                    tree->alloc.deallocate(left_child, 1);
                    left_child = 0;
                }
            } else {
                if (nd.left_child) {
                    left_child = tree->alloc.allocate(1);
                    tree->alloc.construct(left_child, *tree, *nd.left_child);
                    left_child->parent = this;
                } else {
                    left_child = 0;
                }
            }
            if (right_child) {
                if (nd.right_child) {
                    *right_child = *nd.right_child;
                    right_child->parent = this;
                } else {
                    tree->alloc.destroy(right_child);
                    tree->alloc.deallocate(right_child, 1);
                    right_child = 0;
                }
            } else {
                if (nd.right_child) {
                    right_child = tree->alloc.allocate(1);
                    tree->alloc.construct(right_child, *tree, *nd.right_child);
                    right_child->parent = this;
                } else {
                    right_child = 0;
                }
            }
            return *this;
        }

        bool operator==(const node& n) const {
            return data == n.data && tree == n.tree
                   && ((left_child == 0 && n.left_child == 0)
                       || *left_child == *n.left_child)
                   && ((right_child == 0 && n.right_child == 0)
                       || *right_child == *n.right_child);
        }

        bool operator!=(const node& n) const {
            return !(*this == n);
        }
    };

public:
    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        iterator() {
            ptr = 0;
        }

        iterator(node* p) {
            ptr = p;
        }

        iterator(const iterator& it) {
            ptr = it.ptr;
        }

        iterator& operator=(const iterator& it) {
            ptr = it.ptr;
        }

        bool operator==(const iterator& it) const {
            return ptr == it.ptr;
        }

        bool operator!=(const iterator& it) const {
            return ptr != it.ptr;
        }

        /* DROP?
        bool operator<(const iterator&) const;
        bool operator>(const iterator&) const;
        bool operator<=(const iterator&) const;
        bool operator>=(const iterator&) const; */

        // pre-increment
        iterator& operator++() {
            if (ptr->right_child) {
                ptr = ptr->right_child;
                while (ptr->left_child) {
                    ptr = ptr->left_child;
                }
            } else {
                node *before;
                do {
                    before = ptr;
                    ptr = ptr->parent;
                } while (before == ptr->right_child);
            }
            return *this;
        }

        // post-increment
        iterator operator++(int) {
            iterator old(*this);
            ++(*this);
            return old;
        }

        // pre-decrement
        iterator& operator--() {
            if (ptr->left_child) {
                ptr = ptr->left_child;
                while (ptr->right_child) {
                    ptr = ptr->right_child;
                }
            } else {
                node *before;
                do {
                    before = ptr;
                    ptr = ptr->parent;
                } while (before == ptr->left_child);
            }
            return *this;
        }

        // post-decrement
        iterator operator--(int) {
            iterator old(*this);
            --(*this);
            return old;
        }

        reference operator*() const {
            return ptr->data;
        }

        pointer operator->() const {
            return &(ptr->data);
        }
    protected:
        node *ptr;
    };

    /* DROP?
    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference const_reference;
        typedef typename A::pointer const_pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        const_iterator ();
        const_iterator(node*); ??? Where does the const go?
        const_iterator (const const_iterator&);
        const_iterator (const iterator&);
        ~const_iterator();

        const_iterator& operator=(const const_iterator&);
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
        bool operator<(const const_iterator&) const;
        bool operator>(const const_iterator&) const;
        bool operator<=(const const_iterator&) const;
        bool operator>=(const const_iterator&) const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const_iterator& operator+=(size_type);
        const_iterator operator+(size_type) const;
        friend const_iterator operator+(size_type, const const_iterator&);
        const_iterator& operator-=(size_type);
        const_iterator operator-(size_type) const;
        difference_type operator-(const_iterator) const;

        const_reference operator*() const;
        const_pointer operator->() const;
        const_reference operator[](size_type) const;
    };*/

    //typedef std::reverse_iterator<iterator> reverse_iterator;
    //typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    avl_tree() : root(*this) {
        root.n = 0;
    }
    avl_tree(const avl_tree& t) {
        *this = t;
    }
    ~avl_tree() {
        clear();
    }

    avl_tree& operator=(const avl_tree& t) {
        root = t.root;
        return *this;
    }

    bool operator==(const avl_tree& t) const {
        return root == t.root;
    }

    bool operator!=(const avl_tree& t) const {
        return root != t.root;
    }

    iterator begin() {
        node *ptr = &root;
        while (ptr->left_child) {
            ptr = ptr->left_child;
        }
        return iterator(ptr);
    }

    //const_iterator begin() const;
    //const_iterator cbegin() const;

    iterator end() {
        return iterator(&root);
    }

    //const_iterator end() const;
    //const_iterator cend() const;
    //reverse_iterator rbegin();
    //const_reverse_iterator rbegin() const;
    //const_reverse_iterator crbegin() const;
    //reverse_iterator rend();
    //const_reverse_iterator rend() const;
    //const_reverse_iterator crend() const;

    reference front() {
        iterator b = begin();
        return *b;
    }

    const_reference front() const {
        iterator b = begin();
        return *b;
    }

    reference back() {
        iterator b = end();
        return *(--b);
    }

    const_reference back() const {
        iterator b = end();
        return *(--b);
    }

    iterator insert(const T& t) {
        // descent the search tree
        node *parent = &root;
        while (true) {
            ++parent->n;
            if (parent == &root || t < parent->data) {
                if (parent->left_child) {
                    parent = parent->left_child;
                } else {
                    parent->left_child = alloc.allocate(1);
                    alloc.construct(parent->left_child, *this, t);
                    parent->left_child->parent = parent;
                    return iterator(parent->left_child);
                }
            } else {
                if (parent->right_child) {
                    parent = parent->right_child;
                } else {
                    parent->right_child = alloc.allocate(1);
                    alloc.construct(parent->right_child, *this, t);
                    parent->right_child->parent = parent;
                    return iterator(parent->right_child);
                }
            }
        }
    }

    // DROP? iterator insert(T&&);

    reference operator[](size_type i) {
        // bounds checking
        if (i >= size()) {
            throw std::out_of_range("avl_tree[] out-of-range");
        }

        node *ptr = root.left_child;
        while (true) {
            if (i < ptr->n) {
                ptr = ptr->left_child;
            } else if (i == ptr->n) {
                return ptr->data;
            } else {
                i -= ptr->n;
                ptr = ptr->right_child;
            }
        }
    }

    const_reference operator[](size_type i) const {
        // bounds checking
        if (i >= size()) {
            throw std::out_of_range("avl_tree[] out-of-range");
        }

        node *ptr = root.left_child;
        while (true) {
            if (i < ptr->n) {
                ptr = ptr->left_child;
            } else if (i == ptr->n) {
                return ptr->data;
            } else {
                i -= ptr->n;
                ptr = ptr->right_child;
            }
        }
    }

    // make argument const_iterator once its implemented
    iterator erase(iterator it) {
        node *parent = it->parent;
        node *ptr = it.ptr;
        alloc.destroy(ptr);
        alloc.deallocate(ptr, 1);
        while (parent) {
            --parent->n;
            parent = parent->parent;
        }
    }

    // DROP? void remove(const_reference);

    void clear() {
        alloc.destroy(root.left_child);
        alloc.deallocate(root.left_child, 1);
        root.left_child = 0;
    }

    /*template<typename iter>
    void assign(iter, iter);
    void assign(std::initializer_list<T>);
    void assign(size_type, const T&);

    void swap(const avl_tree&);*/

    size_type size() {
        return root.n;
    }

    size_type max_size();

    bool empty() {
        return root.left_child == 0;
    }

    A get_allocator() {
        return alloc;
    }

private:
    using NodeAlloc = typename std::allocator_traits<A>::template rebind_alloc<node>;
    NodeAlloc alloc;
    node root;
};
//template <typename T, typename A = std::allocator<T> >
//void swap(X<T,A>&, X<T,A>&);

#endif
