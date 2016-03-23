#ifndef CAN_BE_CHECKED
#define CAN_BE_CHECKED

#include <type_traits>
#include <tuple>


template <class U, typename T = void>
struct can_be_checked
{
    using type = std::false_type ;
};

template <typename U>
struct can_be_checked<U, typename std::enable_if< ! std::is_class<U>::value >::type> {
    using type = std::true_type ;
};
template <typename U>
struct can_be_checked<U,decltype(&U::operator())> {
    using type = std::true_type ;
};

/*
template  <  class T, typename U = void >
std::false_type can_be_checked() ;


template <class T>
std::true_type can_be_checked<T,typename std::enable_if < ! std::is_class<T>::value >::type()> ();


template <class T>
std::true_type can_be_checked<T,decltype(&T::operator())> ();
*/




#endif // CAN_BE_CHECKED
