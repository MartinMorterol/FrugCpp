#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <functional>

//#include "iterateurFoncteur.hpp"
#include "paramInfo.hpp"
#include "can_be_check.hpp"
#include "type_traits.hpp"
/*
struct Bidon {
    int a = 5 ;
    int b = 6 ;
    int c = 7 ;

    std::vector<std::reference_wrapper<int>> vec;


    Bidon() {
        vec.push_back(std::ref(a));
        vec.push_back(std::ref(b));
        vec.push_back(std::ref(c));
    }

    // Le parcourt des cases
    using iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,std::UnWrappe<int>>;
    using const_iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::const_iterator,std::UnWrappe<int>>;

    inline iterator begin()                     { return iterator(vec.begin());         }
   // inline const_iterator begin() const         { return const_iterator(vec.begin());   }
    inline iterator end()                       { return iterator(vec.end());           }
    //inline const_iterator end() const           { return const_iterator(vec.end());     }
};
*/




template<class InputIterator, class UnaryPredicate,
                class U = typename std::enable_if <  !std::is_class<UnaryPredicate>::value >::type,
                class V = typename std::enable_if < has_operator_parenthese<UnaryPredicate>::value >::type,
                class W = typename std::enable_if < has_operator_parenthese<UnaryPredicate>::value >::type
            >
InputIterator find_if_maison (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    static_assert(nbParam<UnaryPredicate>()==1,"La fonction ne doit avoir qu'un seul parametre !");
   /* static_assert(
        std::is_convertible<typename InputIterator::value_type,
                            decltype(typeParam<0,UnaryPredicate>())>::value,
                  "Les types ne sont pas convertible entre eux :)"
                );

    static_assert(std::is_same<bool,decltype(typeRetour<UnaryPredicate>())>::value,
                  "La méthode doit retourner un bool");*/
    return std::find_if(first,last,pred);
}

template<class InputIterator, class UnaryPredicate,
                class U = typename std::enable_if <  std::is_class<UnaryPredicate>::value >::type,
                class V = typename std::enable_if < !has_operator_parenthese<UnaryPredicate>::value >::type
            >
InputIterator find_if_maison (InputIterator first, InputIterator last, UnaryPredicate pred)
{
    return std::find_if(first,last,pred);
}

template <class T>
bool foo (T a) { (void)a; return true;}

int test2 () { return 1 ;}
bool ok (){ return true;}

struct mem_test {
    bool test(int a, int d) { (void) a; return true ; }
    bool operator()(){return false;}
};
int main()
{
    using namespace std;
    cout << boolalpha ;
    cout << has_operator_parenthese<int>::value << endl;
    cout << has_operator_parenthese<mem_test>::value << endl;

    std::vector<int> test =  { 1 ,2 ,3 , 4 };
  //  auto it = find_if_maison(test.begin(), test.end() ,[](int s){(void)s; return true;} );
   //auto test3 = std::find_if(test.begin(), test.end(), 5);
   //auto test4 = find_if_maison(test.begin(), test.end() ,5 );

  //  auto test5 = find_if_maison(test.begin(), test.end() ,[](int x) { return foo(x); });
    //auto test6 = find_if(test.begin(), test.end() ,foo<int> );

    //auto test6 = find_if(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    auto test7 = find_if_maison(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    exit(5);
    /*cout << nbParam(test2) << endl;

    cout << typeid(can_be_checked<int>::type).name() << endl;
    cout << typeid(can_be_checked<decltype(test2)>::type).name() << endl;
    auto a = [](auto d) { return true ; };

    auto b = [](int s){(void)s; return true;};
    cout << typeid(can_be_checked<decltype(a)>::type).name() << endl;
    cout << typeid(can_be_checked<decltype(b)>::type).name() << endl;*/
    /*std::vector<int> vec =  { 1 ,2 ,3 , 4 };




   cout << enable_if_ope_parentese<int>::value2 << endl;
    cout << enable_if_ope_parentese<mem_test>::value2 << endl;
    std::cout << typeid(decltype(&mem_test::operator())).name() << std::endl;
    std::cout << typeid(decltype(&mem_test::operator())).name() << std::endl;

    //auto test7 = find_if_maison(vec.begin(), vec.end() ,[](auto s){(void)s; return true;} );
    auto test7 = find_if_maison(vec.begin(), vec.end() ,[](int s){(void)s; return true;} );*/
//    cout << nbParam(mem_fun(&mem_test::test) ) << endl;

    /*
    cout << nbParam(&mem_test::test) << endl;
    std::vector<int> vec =  { 1 ,2 ,3 , 4 };
    auto test = find_if_maison(vec.begin(), vec.end() ,&mem_test::test );*/
    //cout << "fail "<< nbParam() << endl;*/


/*
    std::vector<int> test =  { 1 ,2 ,3 , 4 };
  //  auto it = find_if_maison(test.begin(), test.end() ,[](int s){(void)s; return true;} );
   //auto test3 = std::find_if(test.begin(), test.end(), 5);
   //auto test4 = find_if_maison(test.begin(), test.end() ,5 );

    auto test5 = find_if_maison(test.begin(), test.end() ,[](int x) { return foo(x); });
    //auto test6 = find_if(test.begin(), test.end() ,foo<int> );

    //auto test6 = find_if(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    //auto test7 = find_if_maison(test.begin(), test.end() ,[](auto s){(void)s; return true;} );
    cout << *it << endl;



    cout << typeid(decltype(typeParam<0>(mem_fun(&string::length)))).name() << endl;
    cout << typeid(decltype(typeRetour(mem_fun(&string::length)))).name() << endl;
    cout << "ici" << nbParam(mem_fun(&string::length)) << endl;
    Bidon b;
    for (auto& elem : b) {
        std::cout << elem << std::endl;
    }


    //auto monIterateurBegin =  FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,decltype(maLambda)>(b.vec.begin(),maLambda);

    auto maLambda = [] (const std::reference_wrapper<int>& refWrap ) { return refWrap.get(); };
    //auto maLambda = [] ( auto refWrap ) { return refWrap.get(); };

//    cout << typeid(decltype(can_be_checked<int>()).name() << endl;
    /*cout << nbParam(maLambda) <<endl;
    cout << typeid(const std::reference_wrapper<int>&).name() << endl;
    cout << typeid(decltype(typeParam<0>(maLambda))).name() << endl;
    cout << typeid(int).name() << endl;
    cout << typeid(decltype(typeRetour(maLambda))).name() << endl;*/
    can_be_checked<int>::type testqsdf;

    return 0;
}
