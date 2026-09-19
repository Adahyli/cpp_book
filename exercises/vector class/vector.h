
#pragma once

#include <initializer_list>
#include <memory>

template<typename T, typename A = std::allocator<T>>
struct Vector_rep {

    A alloc; 
    int sz; 
    T* elem; 
    int space; 

    Vector_rep(const A& a, int n)
        : alloc{ a }, sz{ n }, elem{ alloc.allocate(2 * n) }, space{ 2 * n } { }
    ~Vector_rep() { alloc.deallocate(elem, space); }

    Vector_rep(Vector_rep&& arg)
        : alloc{std::move(arg.alloc)},
        sz{arg.sz},
        elem{arg.elem},
        space{arg.space}
    {
        arg.sz = 0;
        arg.elem = nullptr;
        arg.space = 0;
    }
};


template<typename T, typename A = std::allocator<T>>
class Vector {

    Vector_rep<T,A> r;
    
public:

    Vector() :  r{A{},0} { }
    explicit Vector(int s) : r{A{}, s}
    {
        for (int i = 0; i < r.sz; ++i)
            std::allocator_traits<A>::construct(r.alloc, r.elem + i, 0);
    }

    Vector(std::initializer_list<T>); // list initializer
    Vector& operator=(std::initializer_list<T>); // list assignment

    Vector(const Vector&); // copy constructor
    Vector& operator=(Vector); // copy assignment

    Vector(Vector&&); // move constructor
    Vector& operator=(Vector&&); // move assignment

    ~Vector() = default;

    T& operator[](int n) { return r.elem[n]; } // access: return reference
    const T& operator[](int n) const { return r.elem[n]; }

    int size() const { return r.sz; }
    int capacity() const { return r.space; }

    
    void reserve(int newalloc);
    void resize(int newsize); // growth
    void push_back(T d);
    

    T* begin() const { return r.elem; } // iteration support
    T* end() const { return r.elem + r.sz; }
};

template<typename T, typename A>
bool operator==(const Vector<T,A>& v1, const Vector<T,A> &v2);

template<typename T, typename A >
bool operator!=(const Vector<T,A>& v1, const Vector<T,A> &v2);

#include "vector.tpp"