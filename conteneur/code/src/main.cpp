#include <utility>
#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <fstream>
#include <vector>
#include <string>
using std::vector;
#include <typeinfo>

#include "lib/fonction_string.hpp"
#include "lib/convertion.hpp"

using namespace libRabbit;

#include <list>

#include <initializer_list>
#include <functional>


namespace brigant {
    template<typename T> struct type_ { using type = T; };


    template<class F, class...Ts> F for_each_args(F f, Ts&&...a)
    {
        return (void)std::initializer_list<int>{((void)std::ref(f)(static_cast<Ts&&>(a)),0)...}, f;
    }

    template<template<class...> class List, typename... Elements, typename Functor>
    Functor for_each_impl( List<Elements...>&&, Functor f )
    {
        return for_each_args( f, type_<Elements>()... );
    }


    template<typename List, typename Functor> Functor for_each( Functor f )
    {
        return for_each_impl( List{}, f );
    }
}

namespace martin {
   



    template<
                template<class...> class List,
                typename... Elements,
                template<class> class Functor
            >
    Functor for_each_impl( List<Elements...>&&, Functor f )
    {
        return (void)std::initializer_list<int>{((void)std::ref(f<Elements...>)(static_cast<Ts&&>()),0)...}, f;
    }


    template<typename List, typename Functor> Functor for_each( Functor f )
    {
        return for_each_impl( List{}, f );
    }
}

struct affiche_typeid
{
    template <typename U>
    void operator()(const U& u)
    {
        std::cout << typeid(u).name() << '\n';
    }
};

struct affiche_typeid2
{
    template <typename U>
    void operator()()
    {
        std::cout << typeid(U()).name() << '\n';
    }
};

int main(int argc, char** argv)
{

    
    brigant::for_each<std::tuple<int,int,double>>(affiche_typeid());
    cout << "__________________" << endl;	
    martin::for_each<std::tuple<int,int,double>>(affiche_typeid2());
   
}
