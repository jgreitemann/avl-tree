#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>
#include <string>
#include <algorithm>
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
        short depth;
        size_type n;
        node *parent;
        node *left_child;
        node *right_child;

        node(avl_tree& tree) : tree(&tree) {
            depth = 1;
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
            depth = 1;
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
            depth = nd.depth;
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

        #ifdef DEBUGMODE
        void print(std::ostream& os, std::string prefix) {
            os << "(" << data << "," << n << "," << depth << ")" << std::endl;
            if (!left_child && !right_child)
                return;
            if (left_child) {
                os << prefix << "+---";
                left_child->print(os, prefix + "|   ");
            } else {
                os << prefix << "+" << std::endl;
            }
            if (right_child) {
                os << prefix << "+---";
                right_child->print(os, prefix + "    ");
            } else {
                os << prefix << "+" << std::endl;
            }
        }
        #endif

        void update_depth() {
            depth = 1 + std::max(left_child ? left_child->depth : 0,
                                 right_child ? right_child->depth : 0);
        }
    };

public:
    class iterator {
        template <typename U, typename V>
        friend class avl_tree<U,V>::const_iterator;
        friend class avl_tree;
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
            return *this;
        }

        bool operator==(const iterator& it) const {
            return ptr == it.ptr;
        }

        bool operator!=(const iterator& it) const {
            return ptr != it.ptr;
        }

        bool operator<(const iterator& it) const {
            return **this < *it;
        }

        bool operator>(const iterator& it) const {
            return **this > *it;
        }

        bool operator<=(const iterator& it) const {
            return **this <= *it;
        }

        bool operator>=(const iterator& it) const {
            return **this >= *it;
        }

        // pre-increment
        iterator& operator++() {
            if (ptr->right_child) {
                ptr = ptr->right_child;
                while (ptr->left_child) {
                    ptr = ptr->left_child;
                }
            } else {
                node* before;
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
                node* before;
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
    private:
        node *ptr;
    };

    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference const_reference;
        typedef typename A::pointer const_pointer;
        typedef std::bidirectional_iterator_tag iterator_category;

        const_iterator () {
            ptr = 0;
        }

        const_iterator(const node* p) {
            ptr = p;
        }

        const_iterator (const const_iterator& it) {
            ptr = it.ptr;
        }

        const_iterator (const iterator& it) {
            ptr = it.ptr;
        }

        const_iterator& operator=(const const_iterator& it) {
            ptr = it.ptr;
            return *this;
        }

        bool operator==(const const_iterator& it) const {
            return ptr == it.ptr;
        }

        bool operator!=(const const_iterator& it) const {
            return ptr != it.ptr;
        }

        bool operator<(const const_iterator& it) const {
            return **this < *it;
        }

        bool operator>(const const_iterator& it) const {
            return **this > *it;
        }

        bool operator<=(const const_iterator& it) const {
            return **this <= *it;
        }

        bool operator>=(const const_iterator& it) const {
            return **this >= *it;
        }

        // pre-increment
        const_iterator& operator++() {
            if (ptr->right_child) {
                ptr = ptr->right_child;
                while (ptr->left_child) {
                    ptr = ptr->left_child;
                }
            } else {
                const node* before;
                do {
                    before = ptr;
                    ptr = ptr->parent;
                } while (before == ptr->right_child);
            }
            return *this;
        }

        // post-increment
        const_iterator operator++(int) {
            iterator old(*this);
            ++(*this);
            return old;
        }

        // pre-decrement
        const_iterator& operator--() {
            if (ptr->left_child) {
                ptr = ptr->left_child;
                while (ptr->right_child) {
                    ptr = ptr->right_child;
                }
            } else {
                const node* before;
                do {
                    before = ptr;
                    ptr = ptr->parent;
                } while (before == ptr->left_child);
            }
            return *this;
        }

        // post-decrement
        const_iterator operator--(int) {
            iterator old(*this);
            --(*this);
            return old;
        }

        const_reference operator*() const {
            return (const_reference)(ptr->data);
        }

        const_pointer operator->() const {
            return &(ptr->data);
        }
    private:
        const node *ptr;
    };

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

    const_iterator begin() const {
        const node *ptr = &root;
        while (ptr->left_child) {
            ptr = ptr->left_child;
        }
        return const_iterator(ptr);
    }

    const_iterator cbegin() const {
        const node *ptr = &root;
        while (ptr->left_child) {
            ptr = ptr->left_child;
        }
        return const_iterator(ptr);
    }

    iterator end() {
        return iterator(&root);
    }

    const_iterator end() const {
        return const_iterator(&root);
    }

    const_iterator cend() const {
        return const_iterator(&root);
    }

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
        iterator res;

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
                    res = iterator(parent->left_child);
                    break;
                }
            } else {
                if (parent->right_child) {
                    parent = parent->right_child;
                } else {
                    parent->right_child = alloc.allocate(1);
                    alloc.construct(parent->right_child, *this, t);
                    parent->right_child->parent = parent;
                    res = iterator(parent->right_child);
                    break;
                }
            }
        }
        short branch_depth = 1;
        do {
            if (parent->depth > branch_depth)
                break;
            parent->depth = 1 + branch_depth;
            branch_depth = parent->depth;
            parent = parent->parent;
        } while(parent);
        return res;
    }

    reference operator[](size_type i) {
        // bounds checking
        if (i >= size()) {
            throw std::out_of_range("avl_tree[] out-of-range");
        }

        size_type j = i;
        node *ptr = root.left_child;
        while (true) {
            if (ptr->left_child) {
                if (j == ptr->left_child->n) {
                    break;
                } else if (j < ptr->left_child->n) {
                    ptr = ptr->left_child;
                } else {
                    j -= 1 + ptr->left_child->n;
                    ptr = ptr->right_child;
                }
            } else {
                if (j == 0) {
                    break;
                } else {
                    --j;
                    ptr = ptr->right_child;
                }
            }
        }
        return ptr->data;
    }

    const_reference operator[](size_type i) const {
        // bounds checking
        if (i >= size()) {
            throw std::out_of_range("avl_tree[] out-of-range");
        }

        size_type j = i;
        const node *ptr = root.left_child;
        while (true) {
            if (ptr->left_child) {
                if (j == ptr->left_child->n) {
                    break;
                } else if (j < ptr->left_child->n) {
                    ptr = ptr->left_child;
                } else {
                    j -= 1 + ptr->left_child->n;
                    ptr = ptr->right_child;
                }
            } else {
                if (j == 0) {
                    break;
                } else {
                    --j;
                    ptr = ptr->right_child;
                }
            }
        }
        return ptr->data;
    }

    iterator erase(iterator it) {
        iterator itn(it);
        ++itn;
        node *ptr = it.ptr;
        node *q;
        if (!ptr->left_child || !ptr->right_child) {
            q = ptr;
        } else {
            q = itn.ptr;
        }
        node *s;
        if (q->left_child) {
            s = q->left_child;
            q->left_child = 0;
        } else {
            s = q->right_child;
            q->right_child = 0;
        }
        if (s) {
            s->parent = q->parent;
        }
        if (q == q->parent->left_child) {
            q->parent->left_child = s;
        } else {
            q->parent->right_child = s;
        }
        if (q != ptr) {
            ptr->data = q->data;
            itn = iterator(ptr);
        }
        node *parent;
        for (parent = q->parent; parent; parent = parent->parent) {
            --parent->n;
            parent->update_depth();
        }
        alloc.destroy(q);
        alloc.deallocate(q, 1);
        return itn;
    }

    iterator find(const_reference t) {
        node *ptr = root.left_child;
        while (ptr) {
            if (t == ptr->data) {
                return iterator(ptr);
            } else if (t < ptr->data) {
                ptr = ptr->left_child;
            } else {
                ptr = ptr->right_child;
            }
        }
        return end();
    }

    void remove(const_reference t) {
        iterator it = find(t);
        if (it == end())
            return;
        do {
            it = erase(it);
        } while(*it == t);
    }

    void clear() {
        if (root.left_child) {
            alloc.destroy(root.left_child);
            alloc.deallocate(root.left_child, 1);
            root.left_child = 0;
        }
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
    void rotate_left(node *n) {
        node *tmp = n->right_child->left_child;
        if (n == n->parent->left_child) {
            n->parent->left_child = n->right_child;
        } else {
            n->parent->right_child = n->right_child;
        }
        n->right_child->parent = n->parent;
        n->right_child->left_child = n;
        n->parent = n->right_child;
        n->right_child = tmp;
        tmp->parent = n;

        // update depths
        do {
            n->update_depth();
            n = n->parent;
        } while (n);
    }

    void rotate_right(node *n) {
        node *tmp = n->left_child->right_child;
        if (n == n->parent->left_child) {
            n->parent->left_child = n->left_child;
        } else {
            n->parent->right_child = n->left_child;
        }
        n->left_child->parent = n->parent;
        n->left_child->right_child = n;
        n->parent = n->left_child;
        n->left_child = tmp;
        tmp->parent = n;

        // update depths
        do {
            n->update_depth();
            n = n->parent;
        } while (n);
    }

    using NodeAlloc = typename std::allocator_traits<A>::template rebind_alloc<node>;
    NodeAlloc alloc;
    node root;

    #ifdef DEBUGMODE
    template <typename U, typename V>
    friend std::ostream& operator<< (std::ostream& stream, const avl_tree<U,V>& t);
    #endif
};
//template <typename T, typename A = std::allocator<T> >
//void swap(X<T,A>&, X<T,A>&);

#ifdef DEBUGMODE
template <typename T, typename A = std::allocator<T> >
std::ostream& operator<<(std::ostream& os, const avl_tree<T,A>& t) {
    if (!t.root.left_child)
        return os << "(empty)" << std::endl;
    t.root.left_child->print(os, "");
    return os;
}
#endif
#endif
