
#include "vector.h"

#include <algorithm>

Vector::Vector(std::initializer_list<double> lst)
    :sz{lst.end() - lst.begin()}, space{sz * 2}, elem {new double [space]}
{
    std::copy(lst.begin(), lst.end(), elem);
}

Vector& Vector::operator=(std::initializer_list<double> lst){

    double* p = new double[lst.size()];

    std::copy(lst.begin(), lst.end(), p);

    delete[] elem;

    elem = p;
    sz = lst.size();

    return *this;

}

Vector::Vector(const Vector& arg)
    :sz{arg.sz}, space{arg.space}, elem{new double[arg.sz]}
{
    std::copy(arg.elem, arg.elem + sz, elem);
}

Vector& Vector::operator=(const Vector& arg){
    
    double* p = new double[arg.sz];

    std::copy(arg.elem, arg.elem + arg.sz, p);

    delete[] elem;

    elem = p;
    sz = arg.sz;

    return *this;
}

Vector::Vector(Vector&& arg)
    :sz{arg.sz}, space {arg.space}, elem{arg.elem}
{
    arg.sz = 0;
    arg.space = 0;
    arg.elem = nullptr;
  
}

 Vector& Vector::operator=(Vector&& arg){
    if (this != &arg){
        delete[] elem;
        elem = arg.elem;
        space = arg.space;
        sz = arg.sz;

        arg.elem = nullptr;
        arg.space = 0;
        arg.sz = 0;
    }
    return *this;
 }

void Vector::reserve(int newalloc){
    if (newalloc <= space)
        return;

    double* p = new double [newalloc];
    for (int i = 0; i < sz; ++i)
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = newalloc;

}

void Vector::resize(int newsize){
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        elem[i] = 0;
    sz = newsize;
}

void Vector::push_back(double d){
    if (space == 0)
        reserve(8);
    else if (sz==space)
        reserve(space * 2);
    elem[sz] = d;
    ++sz;
    
}

