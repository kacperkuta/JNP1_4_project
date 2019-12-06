#include <iostream>
#include "fibin.h"

int main() {
    static_assert( Fibin<int>::eval<
        Let<
                Var("x"),
                Lit<Fib<5>>,
                Let<
                        Var("y"),
                        Ref<Var("x")>,
                        Let<
                                Var("x"),
                                Lit<Fib<3>>,
                                Ref<Var("y")>
                        >
                >
        >



    >() == 5);


    using f1 = Lambda<Var("x"), Inc10<Ref<Var("x")>>>;
    using f2 = Lambda<Var("f"), Sum<Invoke<Ref<Var("f")>, Lit<Fib<1>>>, Lit<Fib<1>>>>;

    static_assert( Fibin<int>::eval<Invoke<f2, f1>>() == 57 );

    static_assert( Fibin<int>::eval<
            If <
                Eq<
                        Lit<Fib<7>>,
                        Sum<Lit<Fib<6>>, Lit<Fib<5>>>
                >,
                Lit<Fib<1>>,
                Lit<Fib<0>>
            >
    > () == 1);


}