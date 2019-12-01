//
// Created by baka475 on 30.11.19.
//

#ifndef JNP1_4_PROJECT_FIBIN_H
#define JNP1_4_PROJECT_FIBIN_H




template<typename T>
class Fibin {
public:

    template<T v, typename = void>
    struct Fib {
        const static T val = Fib<v-1>::val + Fib<v-2>::val;
    };

    template<typename F>
    struct Fib<0, F> {
        const static T val = 0;
    };

    template<typename F>
    struct Fib<1, F> {
        const static T val = 1;
    };

    template<class Fib>
    struct Lit {
        const static T val = Fib::val;
    };

    template<class C>
    static void print() {
        std::cout << C::val;
    }

};

using True = Fibin<bool>::Fib<true>;
using False = Fibin<bool>::Fib<false>;



#endif //JNP1_4_PROJECT_FIBIN_H
