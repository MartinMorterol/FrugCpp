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

    static_assert(std::is_same<bool,decltype(typeRetour<UnaryPredicate>())>::value,
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
    // static_assert(std::is_callable<UnaryPredicate,typename InputIterator::value_type>::value, "test"); // c++17
    return std::find_if(first,last,pred);
}



template <class T>
bool isNotLambdaTemplate (T a)
{
    (void) a;
    return is_not_lamba_template<T>::value;
}

template <class T>
bool isNotLambdaTemplate ()
{
    return is_not_lamba_template<T>::value;
}

template<class T>
bool foo (const T& t){(void)t; return true;}

int main()
{
    auto lambda_test = [](int s){(void)s; return true;};
    static_assert ( std::is_same<bool, decltype(typeRetour(lambda_test))>::value , "" );
    static_assert (std::is_same<bool,decltype(getInformationParam(lambda_test))::type::result_type>::value , "" );

    using namespace std;
    cout << boolalpha ;
    cout << "[](int a ){}  : "  <<  isNotLambdaTemplate([](int a ){ (void) a ;}) << endl;
    cout << "[](auto a ){}  : " <<  isNotLambdaTemplate([](auto a ){ (void) a ;}) << endl;;
    cout << "int  : "           <<  isNotLambdaTemplate(1) << endl;;

    struct structVide {};

    struct structParenthese {
        bool operator()(int a){(void) a; return true;}
    };

    cout << "structParenthese  : " <<  isNotLambdaTemplate<structParenthese>() << endl; ;
    cout << "structVide  : " <<  isNotLambdaTemplate<structVide>() << endl;;

    std::vector<int> vec =  { 1 ,2 ,3 , 4 };
    auto lambda = [](int s){(void)s; return true;};
    find_if_maison  (vec.begin(), vec.end() ,lambda);
    find_if         (vec.begin(), vec.end() ,lambda);

    find_if(vec.begin(), vec.end() ,        foo<int> );
    find_if_maison(vec.begin(), vec.end() , foo<int> );


    find_if(vec.begin(), vec.end() ,            [](auto s){(void)s; return true;} );
    find_if_maison(vec.begin(), vec.end() ,     [](auto s){(void)s; return true;} );

    structParenthese test;
    find_if(vec.begin(), vec.end() ,        test );
    find_if_maison(vec.begin(), vec.end() , test );

    //find_if(vec.begin(), vec.end(),          5);
    //find_if_maison(vec.begin(), vec.end() ,  5);

    //find_if(vec.begin(), vec.end() ,        [](string s){(void)s; return true;} );
    //find_if_maison(vec.begin(), vec.end() , [](string s){(void)s; return true;} );

    //find_if(vec.begin(), vec.end() ,        [](int s){(void)s; return 5;} );
    //find_if_maison(vec.begin(), vec.end() , [](int s){(void)s; return 5;} );

    //find_if(vec.begin(), vec.end() ,        [](int s, int b){(void)s; return false;} );
    //find_if_maison(vec.begin(), vec.end() , [](int s, int b){(void)s; return false;} );

    return 0;
}
