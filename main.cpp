#include <iostream>
#include "fibin.h"
#include <cassert>

int main() {

    using f1 = Fibin<int>::Lit<Fibin<int>::Fib<1>>;
    using f2 = Fibin<int>::Lit<Fibin<int>::Fib<4>>;
    using f3 = Fibin<int>::Lit<Fibin<int>::Fib<10>>;


    std::cout << Fibin<int>::Inc10<f3>::val;
}


