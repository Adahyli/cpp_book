
#include "vector.h"

#include <algorithm>
#include <memory>


template <typename T, typename A>
Vector<T,A>::Vector(std::initializer_list<T> lst)
    :r{A{}, static_cast<int>(lst.size())}
{
    std::uninitialized_copy(lst.begin(), lst.end(), r.elem);
}

template <typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(std::initializer_list<T> lst){

    Vector<T,A> temp{lst};
    std::swap(*this, temp);
    return *this;

}

template <typename T, typename A>
Vector<T,A>::Vector(const Vector& arg)
    :sz{arg.sz}, space{arg.space}, elem{new T[arg.sz]}
{
    std::copy(arg.elem, arg.elem + sz, r.elem);
}

template<typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(Vector<T,A> arg){

    std::swap(*this, arg); 
    return *this;

}


template <typename T, typename A>
Vector<T,A>::Vector(Vector&& arg)
    : r{std::move(arg.r)}
{
}


template <typename T, typename A>
Vector<T,A>& Vector<T,A>::operator=(Vector&& arg){
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

template <typename T, typename A>
void Vector<T,A>::reserve(int newalloc){
    if (newalloc <= space)
        return;

    T* p = new T [newalloc];
    for (int i = 0; i < sz; ++i)
        p[i] = elem[i];
    delete[] elem;
    elem = p;
    space = newalloc;

}

template <typename T, typename A>
void Vector<T,A>::resize(int newsize){
    reserve(newsize);
    for (int i = sz; i < newsize; ++i)
        elem[i] = 0;
    sz = newsize;
}

template <typename T, typename A>
void Vector<T,A>::push_back(T t){
    if (r.space == 0)
        reserve(8);
    else if (r.sz == r.space)
        reserve(r.space * 2);
    std::allocator_traits<A>::construct(r.alloc, r.elem + r.sz, t);
    ++r.sz;
    
}

template<typename T, typename A>
bool operator==(const Vector<T,A>& v1, const Vector<T,A> &v2){
    if (v1.size() != v2.size())
        return false;

    for (int i = 0; i < v1.size(); ++i)
        if (v1[i] != v2[i])
            return false;

    return true;
}

template<typename T, typename A>
bool operator!=(const Vector<T,A>& v1, const Vector<T,A> &v2){
    return !(v1 == v2);
}

