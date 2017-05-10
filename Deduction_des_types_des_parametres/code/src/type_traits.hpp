#pragma once


#include <type_traits>
template<class T>
struct void_if_valide {
    using type = void;
};

template <class T, class U = void>
struct has_operator_parenthese : std::false_type {};

template <class T>
struct has_operator_parenthese <
                T,
                typename void_if_valide<decltype(&T::operator())>::type
            >  : std::true_type {};


template <class T, class U = void, class V = void>
struct is_not_lamba_template : std::false_type {};

template <class T>
struct is_not_lamba_template <
                T,
                typename std::enable_if < has_operator_parenthese<T>::value, void >::type,
                typename std::enable_if < std::is_class<T>::value , void  >::type
            >  : std::true_type {};

template <class T>
struct is_not_lamba_template <
                T,
                typename std::enable_if < ! std::is_class<T>::value , void  >::type,
                void
            >  : std::true_type {};


