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
       out << val << " " ;
    }
    return out;
}

template < class T>
void foo (T&& t) {
    foo(std::forward<T>(t), is_container<T> ());
   //  foo(t, is_container<T> ());
   
}

template < class T>
// void foo  ( T& t , std::true_type default = std::true_type()  ) ??
void foo  (T&& t , std::true_type  )
{
    (void)t;
    std::cout<<"je match les conteneurs"<<std::endl;
}
template < class T>
void foo  (T&& t , std::false_type   )
{
    (void)t;
    std::cout<<"je match pas les conteneurs"<<std::endl;
}
int main() {
    using namespace std;
    std::vector<int> vec = { 1 ,1 ,2, 3, 5 };
    auto init = { 1 ,1 ,2, 3, 5 , 8 };
    cout << vec << endl;
    cout << init << endl;
    foo(vec);
    foo(1);
}
 
