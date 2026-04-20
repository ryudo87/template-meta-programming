# template-meta-programming
C++ templates / CRTP / specialization

## build
g++ -std=c++17 main.cpp -o main

##CRTP (Curiously Recurring Template Pattern) 

2. Object Counting
If you want to track how many instances of various classes exist, you can write a single CRTP counter rather than rewriting the logic for every class.


3. Method Chaining (Fluent Interfaces)

CRTP allows a base class to return a reference to the derived type, which is essential for "fluent" APIs where 
you chain method calls like obj.setName("Gemini").setAge(1).build();.

## Performance: Virtual vs. CRTP
The primary performance difference lies in Indirection and Inlining.

Virtual Calls: Require a lookup in the Virtual Method Table (vtable) at runtime. 
This prevents the compiler from inlining the function 
because it doesn't know which function will be called until the code is actually running.

CRTP Calls: Resolved at compile time. The compiler knows exactly which function is being called and 
can inline the code directly into the call site, eliminating function call overhead entirely.
