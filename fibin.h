//Fibin - functional programming language
//Created by Kacper Kuta and Bartosz Wałachowski

#ifndef JNP1_4_PROJECT_FIBIN_H
#define JNP1_4_PROJECT_FIBIN_H

#include <cstdint>
#include <typeinfo>

constexpr uint64_t length(const char* key) {
    uint64_t l = 0;
    for(size_t i = 0; key[i] != '\0'; ++i) {
        ++l;
    }
    return l;
}

constexpr uint64_t Var(const char* key) {
    uint64_t l = length(key);

    if (l == 0 || l > 6) {
        throw "wrong identifier length!";
    }

   uint64_t  hashed = 0;
   uint64_t  multiplier = 1;

    for(size_t i = 0; i < l; ++i) {
        if(key[i] >= 'A' && key[i] <= 'Z') {
            hashed += key[i] * multiplier;
        }
        else if(key[i] >= '0' && key[i] <= '9') {
            hashed += key[i] * multiplier;
        }
        else if(key[i] >= 'a' && key[i] <= 'z') {
            hashed += (key[i] - ('a' - 'A')) * multiplier;
        }
        else {
            throw "sign not permitted!";
        }
        multiplier *= 100;
    }
    return hashed;
}


//literals
template<uint64_t v>
struct Fib {
    constexpr static uint64_t val = Fib<v - 1>::val + Fib<v - 2>::val;
};

template<>
struct Fib<0> {
    constexpr static uint64_t val = 0;
};

template<>
struct Fib<1> {
    constexpr static uint64_t val = 1;
};

template<typename V>
struct Lit {
    constexpr static uint64_t val = V::val;
};

struct True {
    constexpr static bool val = true;
};
struct False {
    constexpr static bool val = false;
};

template <uint64_t v>
struct Result {
    static constexpr uint64_t val = v;
};

template <typename Arg1, typename Arg2>
struct Eq {};

template <typename Cond, typename Then, typename Else>
struct If {};

template <typename Arg1, typename Arg2, typename ... Args>
struct Sum {};

template <typename Arg>
struct Inc1 {};

template <typename Arg>
struct Inc10 {};

template <uint64_t name>
struct Ref {};

template <uint64_t name, typename Body>
struct Lambda {};

template <typename Fun, typename Arg>
struct Invoke {};

template <typename Body, typename Env, typename Val>
struct Apply {};

template <uint64_t var, typename Val, typename Expr>
struct Let {};

template <uint64_t v1, uint64_t v2>
struct NumberEq {};


//Enviroments and binding const char* id with literal value
struct EmptyEnv;

template <uint64_t name, typename Value, typename LocEnv, typename Env>
struct Binding {};

template <uint64_t name, typename Env>
struct EnvLookup {};

template <uint64_t name>
struct EnvLookup <name, EmptyEnv> {};

template <uint64_t name, typename Value, typename LocEnv, typename Env>
struct EnvLookup <name, Binding<name, Value, LocEnv, Env>> {
    typedef Value result;
    typedef LocEnv env;
};

template <uint64_t name, uint64_t name2, typename Value2, typename Env, typename LocEnv>
struct EnvLookup <name, Binding<name2, Value2, LocEnv, Env>> {
    typedef typename EnvLookup<name, Env> :: result result;
    typedef typename EnvLookup<name, Env> :: env env;
};


//Evaluations
template <typename Arg, typename Env>
struct Eval {};

template <typename Env>
struct Eval<True, Env> {
    typedef True result;
};

template <typename Env>
struct Eval<False, Env> {
    typedef False result;
};

template <typename V, typename Env>
struct Eval<Lit<V>, Env> {
    typedef Lit<V> result;
};

template <uint64_t v, typename Env>
struct Eval<Result<v>, Env> {
    typedef Result<v> result;
};

//Equals

template <uint64_t v1, uint64_t v2, typename Env>
struct Eval<NumberEq<v1, v2>, Env> {
    typedef Lit<False> result;
};

template <uint64_t v1,  typename Env>
struct Eval<NumberEq<v1, v1>, Env> {
    typedef Lit<True> result;
};

template <typename Arg1, typename Arg2,  typename Env>
struct Eval<Eq<Arg1, Arg2>, Env> {
    typedef typename Eval<NumberEq<
            Eval<Arg1, Env>::result::val,
            Eval<Arg2, Env>::result::val
            >,
            Env>::result result;
};

//If condition
template <typename Then, typename Else, typename Env>
struct Eval<If<Lit<True>, Then, Else>, Env> {
    typename Eval<Then, Env>::result typedef result;
};

template <typename Then, typename Else, typename Env>
struct Eval<If<Lit<False>, Then, Else>, Env> {
    typedef typename Eval<Else, Env>::result result;
};

template <typename Cond, typename Then, typename Else, typename Env>
struct Eval<If<Cond, Then, Else>, Env> {
    typedef typename Eval<If<
            typename Eval<Cond, Env>::result,
            Then, Else>, Env>::result result;
};

//Sum
template <typename Arg1, typename Arg2, typename ... Args, typename Env>
struct Eval<Sum<Arg1, Arg2, Args...>, Env> {
    typedef typename Eval<Sum<
            Arg1, typename Eval<Sum<Arg2, Args...>, Env>::result>,
            Env>::result result;
};

template <typename Arg1, typename Arg2, typename Env>
struct Eval<Sum<Arg1, Arg2>, Env> {
    typedef Result<
            Eval<Arg1, Env>::result::val + Eval<Arg2, Env>::result::val
            > result;
};

//Inc1, Inc10
template <typename Arg, typename Env>
struct Eval<Inc1<Arg>, Env> {
    typedef typename Eval<Sum<Arg, Lit<Fib<1>>>, Env>::result result;
};

template <typename Arg, typename Env>
struct Eval<Inc10<Arg>, Env> {
    typedef typename Eval<Sum<Arg, Lit<Fib<10>>>, Env>::result result;
};


//References
template <uint64_t name, typename Env>
struct Eval<Ref<name>, Env> {
    typedef typename Eval<typename EnvLookup<name, Env>::result,
            Env>::result result;
};

//Lambda expressions
template <uint64_t name, typename Body, typename Env>
struct Eval<Lambda<name, Body>, Env> {
    typedef Lambda<name, Body> result;
};

//Invoke
template <typename Fun, typename Arg, typename Env>
struct Eval<Invoke<Fun, Arg> , Env> {
    typedef typename Apply<
            typename Eval<Fun, Env>::result,
            Env,
            typename Eval<Arg, Env>::result>
            ::result result;
};

//Invoke for Lambda variables
template <uint64_t arg, typename Arg, typename Env>
struct Eval<Invoke<Ref<arg>, Arg> , Env> {
    typedef typename Apply<
            typename EnvLookup<arg, Env>::result,
            typename EnvLookup<arg, Env>::env,
            typename Eval<Arg, Env>::result>
            ::result result;
};

//Application of Lambda
template <uint64_t name, typename Body, typename Env, typename Val>
struct Apply<Lambda<name, Body>, Env, Val> {
    typedef typename Eval<Body, Binding<name, Val, Env, Env>>::result result;
};

//Let
template <uint64_t name, typename Val, typename Expr, typename Env>
struct Eval<Let<name, Val, Expr>, Env> {
    typedef typename Eval<Expr, Binding<name, typename Eval<Val, Env>::result, Env, Env>>::result result;
};

template<typename T>
class Fibin {
public:

    template <typename Expr, typename U = T,
            typename = typename std::enable_if_t<std::is_integral<U>::value>>
    static constexpr T eval() {
        return (T)Eval<Expr, EmptyEnv> :: result :: val;
    }

    template <typename Expr, typename U = T,
            typename = typename std::enable_if_t<!std::is_integral<U>::value>>
    static constexpr void eval() {
        std::cout << "Fibin doesn't support: " << typeid(U).name() << std::endl;
    }

};

#endif //JNP1_4_PROJECT_FIBIN_H
