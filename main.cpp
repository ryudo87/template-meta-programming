#include "CRTP.h"

int main()
{
    ColorPrinter cp;
    cp.print("Hello").SetColor("Red").print("World");

    Base<Derived> b;
    b.interface();
}