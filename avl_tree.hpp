#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <memory>

template <typename T, typename A = std::allocator<node> >
class avl_tree {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    class iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;

        iterator();
        iterator(const iterator&);
        ~iterator();

        iterator& operator=(const iterator&);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const;
        bool operator>(const iterator&) const;
        bool operator<=(const iterator&) const;
        bool operator>=(const iterator&) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(size_type);
        iterator operator+(size_type) const;
        friend iterator operator+(size_type, const iterator&);
        iterator& operator-=(size_type);
        iterator operator-(size_type) const;
        difference_type operator-(iterator) const;

        reference operator*() const;
        pointer operator->() const;
        reference operator[](size_type) const;
    };
    class const_iterator {
    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference const_reference;
        typedef typename A::pointer const_pointer;
        typedef std::random_access_iterator_tag iterator_category;

        const_iterator ();
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
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    avl_tree() {
        root = 0;
    }
    avl_tree(const avl_tree& t) {
        this = t;
    }
    ~avl_tree() {
        clear();
    }

    avl_tree& operator=(const avl_tree& t) {
        if (!root) {
            root = alloc.allocate(1);
            alloc.construct(root, t.root);
        } else {
            *root = *(t.root);
        }
    }
    bool operator==(const avl_tree& t) const {
        return *root == *(t.root);
    }
    bool operator!=(const avl_tree& t) const {
        return *root != *(t.root);
    }

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator crbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crend() const;

    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    iterator insert(const T& t) {
        // descent the search tree
        if (!root) {
            root = alloc.allocate(1);
            alloc.construct(root, t);
        } else {
            node *parent = root;
            while (true) {
                ++parent->n;
                if (t < parent->data) {
                    if (parent->left_child) {
                        parent = parent->left_child;
                    } else {
                        parent->left_child = alloc.allocate(1);
                        alloc.construct(parent->left_child, t);
                        parent->left_child->parent = parent;
                        break;
                    }
                } else {
                    if (parent->right_child) {
                        parent = right_child;
                    } else {
                        parent->right_child = alloc.allocate(1);
                        alloc.construct(parent->right_child, t);
                        parent->right_child->parent = parent;
                        break;
                    }
                }
            }
        }
    }

    iterator insert(T&&);
    reference operator[](size_type);
    const_reference operator[](size_type) const;

    iterator erase(const_iterator);
    void remove(const_reference);
    void clear() {
        alloc.destroy(root);
        alloc.deallocate(root, 1);
        root = 0;
    }
    template<typename iter>
    void assign(iter, iter);
    void assign(std::initializer_list<T>);
    void assign(size_type, const T&);

    void swap(const avl_tree&);
    size_type size() {
        return root->n;
    }
    size_type max_size();
    bool empty() {
        return root == 0;
    }

    A get_allocator();

private:
    class node {
    protected:
        T data;
        short imbalance;
        size_type n;
        node *parent;
        node *left_child;
        node *right_child;

        node() {
            imbalance = 0;
            n = 1;
            parent = 0;
            left_child = 0;
            right_child = 0;
        }
        node(const node& nd) {
            left_child = 0;
            right_child = 0;
            this = nd;
        }
        node(const T& t) {
            data = t;
            imbalance = 0;
            n = 1;
            left_child = 0;
            right_child = 0;
        }
        ~node() {
            if (left_child) {
                alloc.destroy(left_child);
                alloc.deallocate(left_child, 1);
            }
            if (right_child) {
                alloc.destroy(right_child);
                alloc.deallocate(right_child, 1);
            }
        }

        node& operator=(const node& nd) {
            data = nd.data;
            imbalance = nd.imbalance;
            n = nd.n;
            if (left_child) {
                if (nd.left_child) {
                    *left_child = *nd.left_child;
                    left_child->parent = &this;
                } else {
                    alloc.destroy(left_child);
                    alloc.deallocate(left_child, 1);
                    left_child = 0;
                }
            } else {
                if (nd.left_child) {
                    left_child = alloc.allocate(1);
                    alloc.construct(left_child, nd.left_child);
                    left_child->parent = &this;
                } else {
                    left_child = 0;
                }
            }
            if (right_child) {
                if (nd.right_child) {
                    *right_child = *nd.right_child;
                    right_child->parent = &this;
                } else {
                    alloc.destroy(right_child);
                    alloc.deallocate(right_child, 1);
                    right_child = 0;
                }
            } else {
                if (nd.right_child) {
                    right_child = alloc.allocate(1);
                    alloc.construct(right_child, nd.right_child);
                    right_child->parent = &this;
                } else {
                    right_child = 0;
                }
            }
            return this;
        }
    };
    A alloc;
    node *root;
};
template <typename T, typename A = std::allocator<T> >
void swap(X<T,A>&, X<T,A>&);

#endif
