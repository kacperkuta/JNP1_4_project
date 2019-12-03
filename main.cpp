#include <iostream>
//#include "fibin.h"
#include <cassert>

//literals
template<int v, typename = void>
struct Fib {
    constexpr static int val = Fib<v - 1>::val + Fib<v - 2>::val;
};

template<typename F>
struct Fib<0, F> {
    constexpr static int val = 0;
};

template<typename F>
struct Fib<1, F> {
    constexpr static int val = 1;
};

template<typename V>
struct Lit {
};

struct True {
    constexpr static bool val = true;
};
struct False {
    constexpr static bool val = false;
};

template <int v>
struct Result {
    static constexpr int val = v;
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

template <int name>
struct Ref {};

template <int name, typename Body>
struct Lambda {};

template <typename Fun, typename Arg>
struct Invoke {};

template <typename Body, typename Env, typename Val>
struct Apply {};

template <int var, typename Val, typename Expr>
struct Let {};



//Enviroments and binding const char* id with literal value
struct EmptyEnv;

template <int name, typename Value, typename Env>
struct Binding {};

template <int name, typename Env>
struct EnvLookup {};

template <int name>
struct EnvLookup <name, EmptyEnv> {};

template <int name, typename Value, typename Env>
struct EnvLookup <name, Binding<name, Value, Env>>
{
    Value typedef result;
};

template <int name, int name2, typename Value2, typename Env>
struct EnvLookup <name, Binding<name2,Value2,Env> >
{
    typename EnvLookup<name,Env> :: result typedef result ;
} ;


//Evaluations

template <typename Arg, typename Env>
struct Eval {};

template <typename V, typename Env>
struct Eval<Lit<V>, Env> {
    typedef V result;
};

template <int v, typename Env>
struct Eval<Result<v>, Env> {
    typedef Result<v> result;
};

//Equals

template <typename Arg1, typename Env>
struct Eval<Eq<Arg1, Arg1>, Env> {
    typedef True result;
};
//TODO: consider types of v1, v2 - e.g. uint64_t doesn't work
template <int v1, int v2, typename Env>
struct Eval<Eq<Lit<Fib<v1>>, Lit<Fib<v2>>>, Env> {
    typedef False result;
};

template <int v1, typename Env>
struct Eval<Eq<Lit<Fib<v1>>, Lit<Fib<v1>>>, Env> {
    typedef True result;
};

template <typename Arg1, typename Arg2,  typename Env>
struct Eval<Eq<Arg1, Arg2>, Env> {
    typedef typename Eval<Eq<Lit<typename Eval<Arg1, Env>::result>, Lit<typename Eval<Arg2, Env>::result>>, Env>::result result;
};

//If condition
template <typename Then, typename Else, typename Env>
struct Eval<If<True, Then, Else>, Env> {
    typename Eval<Then, Env>::result typedef result;
};

template <typename Then, typename Else, typename Env>
struct Eval<If<False, Then, Else>, Env> {
    typedef typename Eval<Else, Env>::result result;
};

template <typename Cond, typename Then, typename Else, typename Env>
struct Eval<If<Cond, Then, Else>, Env> {
    typedef typename Eval<If<typename Eval<Cond, Env>::result, Then, Else>, Env> :: result result;
};

//Sum
template <typename Arg1, typename Arg2, typename ... Args, typename Env>
struct Eval<Sum<Arg1, Arg2, Args...>, Env> {
    typedef typename Eval<Sum<Arg1, typename Eval<Sum<Arg2, Args...>, Env>::result>, Env>::result result;
};


template <typename Arg1, typename Arg2, typename Env>
struct Eval<Sum<Arg1, Arg2>, Env> {
    typedef Result<Eval<Arg1, Env>::result::val + Eval<Arg2, Env>::result::val> result;
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
template <int name, typename Env>
struct Eval<Ref<name>, Env> {
    typedef typename Eval<typename EnvLookup<name, Env>::result, Env>::result result;
};

//Lambda expressions

//this one seems to be redundant
template <int name, typename Body, typename Env>
struct Eval<Lambda<name, Body>, Env> {

};

template <typename Fun, typename Arg, typename Env>
struct Eval<Invoke<Fun, Arg> , Env> {
    typedef typename Apply<Fun, Env, Lit<typename Eval<Arg, Env>::result>>::result result ;
};

template <int name, typename Body, typename Env, typename Value>
struct Apply<Lambda<name, Body>, Env, Value> {
    typedef typename Eval<Body, Binding<name, Value, Env>>::result result ;
};

template <int name, typename Val, typename Expr, typename Env>
struct Eval<Let<name, Val, Expr>, Env> {
    typedef typename Eval<Expr, Binding<name, Val, Env>>::result result;
};



int  main() {

    //typedef Lambda < 1, Sum<Ref<1>, Lit<Fib<13>>> > Fun;

    std::cout << Eval< Let<1, Lit<Fib<7>>, Sum< Inc10<Ref<1>>, Lit<Fib<5>>, Ref<1>>>, EmptyEnv   >::result::val;
}
