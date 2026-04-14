#include "CRTP.h"

int main()
{
    Base<Derived> b;
    b.interface();
}