
#include "vector.h"

#include <algorithm>

template <typename T>
Vector<T>::Vector(std::initializer_list<T> lst)
    :sz{lst.end() - lst.begin()}, space{sz * 2}, elem {new T [space]}
{
    std::copy(lst.begin(), lst.end(), elem);
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> lst){

    T* p = new T[lst.size()];

    std::copy(lst.begin(), lst.end(), p);

    delete[] elem;

    elem = p;
    sz = lst.size();

    return *this;

}

template <typename T>
Vector<T>::Vector(const Vector& arg)
    :sz{arg.sz}, space{arg.space}, elem{new T[arg.sz]}
{
    std::copy(arg.elem, arg.elem + sz, elem);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& arg){
    
    T* p = new T[arg.sz];

    std::copy(arg.elem, arg.elem + arg.sz, p);

    delete[] elem;

    elem = p;
    sz = arg.sz;

    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& arg)
    :sz{arg.sz}, space {arg.space}, elem{arg.elem}
{
    arg.sz = 0;
    arg.space = 0;
    arg.elem = nullptr;
  
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& arg){
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

template <typename T>
void Vector<T>::reserve(int newalloc){
    if (newalloc <= space)
        return;

    T* p = new T [newalloc];
    for (int i = 0; i < sz; ++i)
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = newalloc;

}

template <typename T>
void Vector<T>::resize(int newsize){
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        elem[i] = 0;
    sz = newsize;
}

template <typename T>
void Vector<T>::push_back(T t){
    if (space == 0)
        reserve(8);
    else if (sz==space)
        reserve(space * 2);
    elem[sz] = t;
    ++sz;
    
}

