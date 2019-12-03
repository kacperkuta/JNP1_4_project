//
// Created by baka475 on 30.11.19.
//

#ifndef JNP1_4_PROJECT_FIBIN_H
#define JNP1_4_PROJECT_FIBIN_H


template<typename T>
class Fibin {
public:
    //literals
    template<T v, typename = void>
    struct Fib {
        constexpr static T val = Fib<v - 1>::val + Fib<v - 2>::val;
    };

    template<typename F>
    struct Fib<0, F> {
        constexpr static T val = 0;
    };

    template<typename F>
    struct Fib<1, F> {
        constexpr static T val = 1;
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

    template <T v>
    struct Result {
        T val = v;
    };

    template <typename Arg1, typename Arg2>
    struct Eq {};

    template <typename Cond, typename Then, typename Else>
    struct If {};

    template <typename Arg1, typename Arg2, typename ... Args>
    struct Sum {};



    //Enviroments and binding const char* id with literal value
    struct EmptyEnv;

    template <int Name, typename Value, typename Env>
    struct Binding {};

    template <int Name, typename Env>
    struct EnvLookup {};

    template <int Name>
    struct EnvLookup <Name,EmptyEnv> {}; // Name not found.

    template <int Name, typename Value, typename Env>
    struct EnvLookup <Name, Binding<Name, Value, Env>>
    {
        Value typedef result;
    };
/*
    template <int Name, int Name2, typename Value2, typename Env>
    struct EnvLookup <Name, Binding<Name2,Value2,Env> >
    {
        typename EnvLookup<Name,Env> :: result typedef result ;
    } ;
*/

//Evaluations

    template <typename Arg, typename Env>
    struct Eval {};

    template <typename V, typename Env>
    struct Eval<Lit<V>, Env> {
        typedef V result;
    };

    template <T v, typename Env>
    struct Eval<Result<v>, Env> {
        typedef Result<v> result;
    };

    //Equals
    template <typename Arg1, typename Env>
    struct Eval<Eq<Arg1, Arg1>, Env> {
        typedef True result;
    };

    //TODO: consider typer of v1, v2 - e.g. uint64_t doesn't work
    template <T v1, T v2, typename Env>
    struct Eval<Eq<Fib<v1>, Fib<v2>>, Env> {
        typedef False result;
    };

    template <typename Arg1, typename Arg2,  typename Env>
    struct Eval<Eq<Arg1, Arg2>, Env> {
        typedef typename Eval<Eq<typename Eval<Arg1, Env>::result, typename Eval<Arg2, Env>::result>, Env>::result result;
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



};

#endif //JNP1_4_PROJECT_FIBIN_H
