
#pragma once

class Ptr {
private:
    double* p;

public:
    explicit Ptr (double val)
    : p {new double{val}}
    {
    }

    explicit Ptr(const Ptr& arg)
    : p{new double{*arg.p}}
    {
    }


    ~Ptr(){
        delete p;
    }

    Ptr& operator=(const Ptr& arg);

    Ptr(Ptr&& arg);

    Ptr& operator=(Ptr&& arg);

    double& operator*();

};