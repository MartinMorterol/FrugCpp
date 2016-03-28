#include <iostream>
#include <vector>
#include <type_traits>




template<class T>
struct void_if_valide {
    using type = void;
};

template <class T, class U = void, class V = void>
struct is_container : std::false_type {};

template <class T>
struct is_container<   T,
                typename void_if_valide<decltype(std::declval<T>().begin())>::type,
                typename void_if_valide<decltype(std::declval<T>().end())>::type
            >  : std::true_type {};

template <class T, class U = void>
struct is_string : std::false_type {};

template <class T>
struct is_string<   T,
                typename void_if_valide<typename std::enable_if<
                                                                std::is_same<T,std::wstring>::value ||
                                                                std::is_same<T,std::string>::value
                                                                >::type
                                        >::type
            >  : std::true_type {};



template<
        class T,
        class V = typename std::enable_if< is_container<T>::value >::type,
        class U = typename std::enable_if< !is_string<T>::value >::type
      >
std::ostream& operator<< (std::ostream& out, const T& container)
{
    for (const auto& val : container)
    {
       // out << "\t" << val << "\n" ;
       out << val << " " ;
    }
    return out;
}
/*
// marche pas
template< class T, class U =  typename std::enable_if< is_container<T>::value  >::type >
void foo (const T& t) {
    std::cout << "je match  les conteneurs" << std::endl;
}
template< class T, class U =  typename std::enable_if< !is_container<T>::value  >::type >
void foo (const T& t) {
    std::cout << "je match pas les conteneurs" << std::endl;
}
*/
/*
template< class T, class U =  typename std::enable_if< is_container<T>::value  >::type >
void foo (const T& t) {
    std::cout << "je match  les conteneurs" << std::endl;
}
template< class T, class U =  typename std::enable_if< !is_container<T>::value  >::type,
          class W =  typename std::enable_if< !is_container<T>::value  >::type>
void foo (const T& t) {
    std::cout << "je match pas les conteneurs" << std::endl;
}
*/
/*
// Marche
template< class T >
typename std::enable_if< is_container<T>::value, void  >::type  foo (const T& t) {
    std::cout << "je match  les conteneurs" << std::endl;
}
template< class T >
typename std::enable_if< ! is_container<T>::value , void  >::type  foo (const T& t) {
    std::cout << "je match pas les conteneurs" << std::endl;
}
*/

int main() {
    using namespace std;
    std::vector<int> vec = { 1 ,1 ,2, 3, 5 };
    cout << vec << endl;
}

// question pour lénaic






/*
template <class T, class U = int >
struct demo
{
    constexpr static int value = 0;
};

template<class T>
struct demo <T,int>
{
    constexpr static int value = 1;
};

template<class T>
struct demo <T,void>
{
    constexpr static int value = 2;
};

int main() {
    using namespace std;
    cout << demo<std::string>::value << endl;
    cout << demo<int,int>::value << endl;
    cout << demo<int,void>::value << endl;
    cout << demo<int,std::string>::value << endl;
}
*/

/*// Le type par defaut doit etre celui de la spécialisaiton
template <class T, class U = int >
struct has_method_foo
{
    // for tag dispatching
    constexpr static bool value = false;

    // no type "type" for SFINAE
};

template<class T>
struct has_method_foo <T,int>
{
    // for tag dispatching
    constexpr static bool value = true;

    // no type "type" for SFINAE
    using type = void;
};

struct fooclass {
    void foo() {}
};
int main() {
    using namespace std;

    cout << boolalpha ;
    cout << has_method_foo<int>::value << endl;
    cout << has_method_foo<fooclass>::value << endl;



}*/
