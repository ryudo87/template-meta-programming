#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
using namespace std;

//fix MyGet() for both tRef and tCpy
template <typename T, typename Tuple>
decltype(auto) MyGet(Tuple&& tuple)
{
    return std::get<T>(std::forward<decltype(tuple)>(tuple));
}

int main()
{
    int i = 1;
    std::string s = "abc";
    auto tRef = std::tie(i, s); // const tuple<int&, string&> tRef = std::tie(i, s);
    auto tCpy = std::make_tuple(i, s);

#if 0
    // this code should also compile with
    auto& t = tCpy;
#else
    // Make this work in a way that a tuple created from std::tie can be accessed from base type.
    auto& t = tRef;
#endif

    MyGet<int>(t) = 2;
    MyGet<std::string>(t) = "def";

    if (i != 2 || s != "def")
    {
        std::cerr << "failure i==" << i << " s=" << s << std::endl;
        return -1;
    }

    std::cout << "success" << std::endl;
}