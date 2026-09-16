
#pragma once

#include <initializer_list>

template<typename T>
class Vector {
/*
 invariant:
 if 0<=n<sz, elem[n] is element n
 sz<=space;
 if sz<space there is space for (space-sz) Ts after elem[sz-1]
*/
    int sz; // the size
    int space; // number of elements plus number of free slots
    T* elem; // pointer to the elements (or 0)
    
public:
    Vector() : sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s) :sz{s}, space{s * 2}, elem{new T[s]}
    {
        for (int i=0; i<sz; ++i)
            elem[i]=0; // elements are initialized
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