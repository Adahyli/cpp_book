
#pragma once

class Ptr {
private:
    double* p;

public:
    explicit Ptr (double val)
    : p {new double{val}}
    {
    }

    Ptr(const Ptr& arg);
    Ptr& operator=(const Ptr& arg);


    ~Ptr(){
        delete p;
    }



    Ptr(Ptr&& arg);
    Ptr& operator=(Ptr&& arg);

    double& operator*();

};