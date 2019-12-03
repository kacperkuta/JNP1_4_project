#include <iostream>
#include "fibin.h"
#include <cassert>


int  main() {


    //Fibin<const char*>::eval< Let<Var("x"), Lit<Fib<14>>, Sum<Ref<Var("x")>, Lit<Fib<1>>>>>  ();



    std::cout << Fibin<int>::eval<Let<Var("f"), Lambda< Var("x"), Inc1<Ref<Var("x")>>>, Invoke<Ref<Var("f")>, Lit<Fib<0>>>>>();

}
