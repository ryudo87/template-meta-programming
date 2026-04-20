//CRTP Curiously Recurring Template Pattern
// class-based static polymorphism without cost of virtual function
// base class takes derived class as a template parameter
#include <iostream>
using namespace std;
//1. Object Counting
// Instead of manually adding a counter to every class, you can create a reusable base.
template<typename T>
class Counter
{
static inline size_t count = 0;
public:
    Counter() {++count;}
    ~Counter() {--count;}
    static size_t getCount() {return count;}
};
class User : public Counter<User> {};
class Message : public Counter<User> {};

//2. Method Chaining (Fluent Interfaces)
// In standard inheritance, if a base class method returns *this, it returns a reference to Base. 
// This breaks the chain if you try to call a Derived method immediately after. CRTP fixes this by casting this to the derived type.
template<typename Derived>
class Printer
{
public: 
    Derived& print(const string& msg) {
        cout<<msg<<endl;
        return static_cast<Derived&>(*this);
    }
};
class ColorPrinter : public Printer<ColorPrinter>
{
public:
    ColorPrinter& SetColor(const string& color) {
        cout<<"Setting color to "<<color<<endl;
        return *this;
    }
};

//====================
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