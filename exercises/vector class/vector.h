
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
        : alloc{ a }, sz{ n }, elem{ alloc.allocate(n) }, space{ n } { }
    ~Vector_rep() { alloc.deallocate(elem, space); }
};

template<typename T, typename A = std::allocator<T>>
class Vector {

    Vector_rep<T,A> r;
    
public:
    Vector() : sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s) : r{A(),s}
    {
        for (int i=0; i < sz; ++i)
            r.elem[i] = 0; 
    }

    Vector(std::initializer_list<T>); // list initializer
    Vector& operator=(std::initializer_list<T>); // list assignment

    Vector(const Vector&); // copy constructor
    Vector& operator=(const Vector&); // copy assignment

    Vector(Vector&&); // move constructor
    Vector& operator=(Vector&&); // move assignment

    ~Vector() { delete[] elem; } // destructor

    T& operator[ ](int n) { return elem[n]; } // access: return reference
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }
    int capacity() const { return space; }

    
    void reserve(int newalloc);
    void resize(int newsize); // growth
    void push_back(T d);
    

    T* begin() const { return elem; } // iteration support
    T* end() const { return elem+sz; }
};

template<typename T>
bool operator==(const Vector<T>& v1, const Vector<T> &v2);

template<typename T>
bool operator!=(const Vector<T>& v1, const Vector<T> &v2);