//
// Created by baka475 on 30.11.19.
//

#ifndef JNP1_4_PROJECT_FIBIN_H
#define JNP1_4_PROJECT_FIBIN_H

#include <unordered_map>


template<typename T>
class Fibin {
public:

    template<T v>
    struct Fib {
        constexpr static T val = Fib<v-1>::val + Fib<v-2>::val;
    };

    template<>
    struct Fib<0> {
        constexpr static T val = 0;
    };

    template<>
    struct Fib<1> {
        constexpr static T val = 1;
    };

    template<class Fib>
    struct Lit {
        constexpr static T val = Fib::val;
    };

    template<class C>
    static void print() {
        std::cout << C::val;
    }

    template<typename ... Args>
    struct Sum {
        constexpr static T val = (... + Args::val);
    };

    template<typename Arg>
    struct Inc1 {
        constexpr static T val = Arg::val + Fib<1>::val;
    };

    template<typename Arg>
    struct Inc10 {
        constexpr static T val = Arg::val + Fib<10>::val;
    };

    template<class Lit1, class Lit2>
    struct Eq {
        constexpr static bool val = (Lit1::val == Lit2::val);
    };

    template<class Cond, class Then, class Else>
    struct If {
        constexpr static T val = Cond::val ? Then::val : Else::val;
    };

    std::string Var(const char* s) {
        return std::string(s);
    }


    template<std::string&& v>
    struct Ref {
        T val = refs[v];
    };

private:
    static std::unordered_map<std::string, T> refs;


};

using True = Fibin<bool>::Fib<true>;
using False = Fibin<bool>::Fib<false>;



#endif //JNP1_4_PROJECT_FIBIN_H
