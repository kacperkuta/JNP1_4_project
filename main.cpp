#include <iostream>
#include "fibin.h"
#include <cassert>


int  main() {


    //Fibin<const char*>::eval< Let<Var("x"), Lit<Fib<14>>, Sum<Ref<Var("x")>, Lit<Fib<1>>>>>  ();
/*
    static_assert(59 == Fibin<uint64_t>::eval<
            Invoke<
                    Lambda<Var("x"),
                            Sum<Ref<Var("x")>, Inc10<Lit<Fib<1>>>, Lit<Fib<2>>>>, Lit<Fib<3>>>>());

    // Testing: if False then Fib(0) else Fib(1)
    static_assert(1 == Fibin<uint8_t>::eval<If<Lit<False>, Lit<Fib<0>>, Lit<Fib<1>>>>());

    // Testing: let z = Fib(0) in {z + Fib(1)}
    static_assert(1 == Fibin<int16_t>::eval<Let<Var("z"), Lit<Fib<0>>, Inc1<Ref<Var("Z")>>>>());

    // Prints out to std::cout: "Fibin doesn't support: PKc"
    Fibin<const char*>::eval<Lit<Fib<0>>>();

    std::cout << "Fibin works fine!" << std::endl;


*/
    //typedef Lambda <Var("x"), Inc1<Ref<Var("x")>>> Fun;

    std::cout << Fibin<std::uint32_t>::eval<
            Let<
                    Var("f"),
                    Lambda<
                            Var("x"),
                            If<
                                    Eq<Ref<Var("x")>, Lit<Fib<5>>>,
                                    Lit<Fib<0>>,
                                    Invoke<Ref<Var("f")>, Lit<Fib<5>>>
                            >
                    >,
                    Invoke<Ref<Var("f")>, Lit<Fib<0>>>
                    >
            >();
    //std::cout << Fibin<int>::eval<Invoke<Ref<Var("f")>, Binding<Var("f"), Fun, EmptyEnv>>>();

}
