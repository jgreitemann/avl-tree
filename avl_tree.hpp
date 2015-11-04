#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <memory>

template <class T, class A = std::allocator<T> >
class avl_tree {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    struct node {
        T data;
        short imbalance;
        int n;
        iterator left_child;
        iterator right_child;
    };

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

    avl_tree();
    avl_tree(const avl_tree&);
    ~avl_tree();

    avl_tree& operator=(const avl_tree&);
    bool operator==(const avl_tree&) const;
    bool operator!=(const avl_tree&) const;

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
    void insert(const T&);
    void insert(T&&);
    reference operator[](size_type);
    const_reference operator[](size_type) const;

    iterator erase(const_iterator);
    void clear();
    template<class iter>
    void assign(iter, iter);
    void assign(std::initializer_list<T>);
    void assign(size_type, const T&);

    void swap(const avl_tree&);
    size_type size();
    size_type max_size();
    bool empty();

    A get_allocator();
};
template <class T, class A = std::allocator<T> >
void swap(X<T,A>&, X<T,A>&);

#endif
