//CRTP Curiously Recurring Template Pattern
// class-based static polymorphism without cost of virtual function
// base class takes derived class as a template parameter
#include <iostream>C
using namespace std;
template <typename Derived>
class Base 
{
public:
    void interface() {
        static_cast<Derived*>(this)->implement();
    }
};

class Derived : public Base<Derived>
{
public:
    void implement() {
        cout<<"Derived::implement"<<std::endl;
    }
};