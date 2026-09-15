
#include "Ptr.h"

Ptr::Ptr(const Ptr& arg)
    : p{new double{*arg.p}}
{
}

Ptr& Ptr::operator=(const Ptr& arg){
    if (this == &arg)
        return *this;
        
    double* temp = new double{*arg.p};
    delete p;
    p = temp;

    return *this;
}

Ptr::Ptr(Ptr&& arg)
    : p{arg.p}
{
    arg.p = nullptr;
}

Ptr& Ptr::operator=(Ptr&& arg)
    {
        if (this == &arg)
            return *this;

        delete p;
        p = arg.p;
        arg.p = nullptr;

        return *this;
    }

    double& Ptr::operator*()
    {
        return *p;
    }
