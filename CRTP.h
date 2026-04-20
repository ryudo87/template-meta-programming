//CRTP Curiously Recurring Template Pattern
// class-based static polymorphism without cost of virtual function
// base class takes derived class as a template parameter
#include <iostream>
#include <variant>
#include <vector>
#include <memory>
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

//=======Token Guard============
// template <typename T>
// class Base 
// {
//     // Base() {}
//     // friend T;
// public:   
//     void interface() {
//         static_cast<T*>(this)->implement();
//     }
// };

// This will fail to compile!
// Base<Derived>'s constructor is private and only 'Derived' is a friend.
// 'BadDerived' cannot access the constructor of Base<Derived>.
// class BadDerived : public Base<Derived> { 
// public:
//     void implement() { std::cout << "BadDerived::implement\n"; }
// };

//=======Because CRTP relies on static polymorphism, 
// Base<D1> and Base<D2> are entirely different, unrelated types. 
// You cannot store them in a std::vector<Base<T>> because T must be a specific type at compile time.

//=======Solution
// 1. The Common Non-Template Base (Hybrid Approach)
// The most common solution is to introduce a non-template abstract base class above the CRTP base.

class IBase {
public:
    virtual void interface() = 0;
    virtual ~IBase() = default;
};

template <typename T>
class Base : public IBase {
public:
    void interface() override {
        static_cast<T*>(this)->implement();
    }
};

class D1 : public Base<D1> {
public:
    void implement() { std::cout << "D1::implement\n"; }
};

class D2 : public Base<D2> {
public:
    void implement() { std::cout << "D2::implement\n"; }
};
    // Usage
std::vector<std::unique_ptr<IBase>> vec;
vec.push_back(std::make_unique<D1>());
vec.push_back(std::make_unique<D2>());


//2. Using std::variant (Type-Safe Union)
//If you know the set of types (D1 and D2) at compile time and want to avoid heap allocation/virtual tables, std::variant is the modern C++ way to handle "closed" polymorphism.

using AnyDerived = std::variant<D1, D2>;
    // std::vector<AnyDerived> vec;
    // vec.push_back(D1{});
    // vec.push_back(D2{});
    // cout<<vec.size()<<endl;