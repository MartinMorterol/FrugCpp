#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <functional>

//#include "iterateurFoncteur.hpp"
#include "paramInfo.hpp"
#include "can_be_check.hpp"
#include "type_traits.hpp"


template<class InputIterator, class UnaryPredicate>
typename std::enable_if <
                            is_not_lamba_template<UnaryPredicate>::value ,
                            InputIterator
                        >::type
find_if_maison (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    static_assert(nbParam<UnaryPredicate>()==1,"La fonction ne doit avoir qu'un seul parametre !");
    static_assert(
        std::is_convertible<typename InputIterator::value_type,
                            decltype(typeParam<0,UnaryPredicate>())>::value,
                  "Les types ne sont pas convertible entre eux :)"
                );

    static_assert( std::is_convertible<bool,decltype(typeRetour<UnaryPredicate>())>::value,
                  "La méthode doit retourner un bool");
    return std::find_if(first,last,pred);
}

template<class InputIterator, class UnaryPredicate>
typename std::enable_if <
                            !is_not_lamba_template<UnaryPredicate>::value,
                            InputIterator
                        >::type
find_if_maison (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    // http://en.cppreference.com/w/cpp/types/is_callable
    // static_assert + std::is_callable // c++17
    return std::find_if(first,last,pred);
}



template <class T>
bool isLambdaTemplate (const T&)
{
    return !is_not_lamba_template<T>::value;
}

template <class T>
bool isLambdaTemplate ()
{
    return !is_not_lamba_template<T>::value;
}

template<class T>
bool foo (const T& ){ return true;}





int main()
{
    std::vector<int> vec =  { 1 ,2 ,3 , 4 };
    auto lambda = [](int ){return true;};
    struct structVide {};
    struct structParenthese {
        bool operator()(int ){ return true;}
    };


    // les using <T>
    static_assert (std::is_same<bool,type_result<decltype(lambda)> >::value , "" );
    static_assert (std::is_same<decltype(typeRetour<structParenthese>())
                                ,type_result<structParenthese> >::value , "" );
    static_assert (std::is_same<decltype(typeParam<0,structParenthese>())
                                ,type_param<0,structParenthese> >::value , "" );
    static_assert (type_nb_param<structParenthese>::arity == 1 , "" );


    using namespace std;
    cout << boolalpha ;
    cout << "[](int a ){}  : "  <<  isLambdaTemplate([](int ){}) << endl;
    cout << "[](auto a ){}  : " <<  isLambdaTemplate([](auto  ){}) << endl;
    cout << "int  : "           <<  isLambdaTemplate(1) << endl;
    cout << "structParenthese  : " <<  isLambdaTemplate<structParenthese>() << endl; ;
    cout << "structVide  : " <<  isLambdaTemplate<structVide>() << endl;;


    find_if_maison  (vec.begin(), vec.end() ,lambda);
    find_if         (vec.begin(), vec.end() ,lambda);

    find_if(vec.begin(), vec.end() ,        foo<int> );
    find_if_maison(vec.begin(), vec.end() , foo<int> );


    find_if(vec.begin(), vec.end() ,            [](auto ){ return true;} );
    find_if_maison(vec.begin(), vec.end() ,     [](auto ){ return true;} );

    structParenthese test;
    find_if(vec.begin(), vec.end() ,        test );
    find_if_maison(vec.begin(), vec.end() , test );

//    find_if(vec.begin(), vec.end(),          5);
//    find_if_maison(vec.begin(), vec.end() ,  5);

    //find_if(vec.begin(), vec.end() ,        [](string ){ return true;} );
    //find_if_maison(vec.begin(), vec.end() , [](string ){ return true;} );

    //find_if(vec.begin(), vec.end() ,        [](int ){ return structParenthese();} );
    //find_if_maison(vec.begin(), vec.end() , [](int ){ return structParenthese();} );

    //find_if(vec.begin(), vec.end() ,        [](int , int ){ return false;} );
//    find_if_maison(vec.begin(), vec.end() , [](int , int ){ return false;} );

    return 0;
}
