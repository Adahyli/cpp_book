
#pragma once

#include <initializer_list>

class Vector {
/*
 invariant:
 if 0<=n<sz, elem[n] is element n
 sz<=space;
 if sz<space there is space for (space-sz) doubles after elem[sz-1]
*/
    int sz; // the size
    int space; // number of elements plus number of free slots
    double* elem; // pointer to the elements (or 0)
    
public:
    Vector() : sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s) :sz{s}, space{s * 2}, elem{new double[s]}
    {
        for (int i=0; i<sz; ++i)
            elem[i]=0; // elements are initialized
    }

    Vector(std::initializer_list<double>); // list initializer
    Vector& operator=(std::initializer_list<double>); // list assignment

    Vector(const Vector&); // copy constructor
    Vector& operator=(const Vector&); // copy assignment

    Vector(Vector&&); // move constructor
    Vector& operator=(Vector&&); // move assignment

    ~Vector() { delete[] elem; } // destructor

    double& operator[ ](int n) { return elem[n]; } // access: return reference
    const double& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }
    int capacity() const { return space; }

    
    void reserve(int newalloc);
    void resize(int newsize); // growth
    void push_back(double d);
    

    double* begin() const { return elem; } // iteration support
    double* end() const { return elem+sz; }
};

bool operator==(Vector& v1, Vector &v2);
bool operator!=(Vector& v1, Vector &v2);