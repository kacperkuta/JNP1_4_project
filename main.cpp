#include <iostream>
#include "fibin.h"
#include <cassert>

int main() {
    Fibin<int>::print<Fibin<int>::Fib<4>>();
}


