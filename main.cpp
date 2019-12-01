#include <iostream>
#include "fibin.h"
#include <cassert>

int main() {
    Fibin<int>::print<Fibin<int>::Lit<Fibin<int>::Fib<13>>>();
}


