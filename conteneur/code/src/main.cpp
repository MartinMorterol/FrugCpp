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

struct affiche_typeid
{
    template <typename U>
    void operator()(const U& u)
    {
        std::cout << typeid(u).name() << '\n';
    }

};



namespace martin {
   
    template <class F, class T> 
    int remove_type_ (F f,T )
    {
        f.template operator()<typename T::type>();
        return 1;
    }
    
    template<typename T> struct type_ { using type = T; };


    template<class F, class...Ts> F for_each_args(F f, Ts&&...a)
    {
        // Danger : j'ai pas compris a quoi servait de "std::ref" ici 
        // et j'ai pas réussi à le remettre dans ma solution
        return (void)std::initializer_list<int>{(remove_type_(f,static_cast<Ts&&>(a)),0)...}, f;
      
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

struct affiche_typeid_martin
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
    martin::for_each<std::tuple<int,int,double>>(affiche_typeid_martin());
   
}
