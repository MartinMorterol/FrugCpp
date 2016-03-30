#pragma once
#ifndef param_info_hpp
#define param_info_hpp

#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <type_traits>
#include "can_be_check.hpp"
#include "type_traits.hpp"

template <class... T>
class ERREUR;

template <class T>
struct informationParam{
    struct IsNotACallable {};
    ERREUR<T,IsNotACallable> erreur;

    /*
    static_assert(
                   std::is_same < T, typename void_if_valide<T>::type >::value &&false
                  ,
                  "L'argument template n'est pas callable"
                  );*/
};


template<class ReturnType, class ... Args>
struct informationParamParamFactorisation
{
    constexpr static size_t arity = sizeof...(Args);
    using  result_type = ReturnType;

    template <size_t indice>
    struct arg_type_
    {
        static_assert ((indice < arity ), "La fonction à moins de param que ce que vous demandez" );
        using type= typename std::tuple_element<indice, std::tuple<Args...>>::type;

    };
    template <size_t i> using arg_type = typename arg_type_<i>::type;
};
// operateur () PAS !!! const
template <typename ClassType, typename ReturnType, typename... Args>
struct informationParam<ReturnType(ClassType::*)(Args...) >
{
    using type = informationParamParamFactorisation<ReturnType,Args...>;
};

// operateur () const
template <typename ClassType, typename ReturnType, typename... Args>
struct informationParam<ReturnType(ClassType::*)(Args...) const>
{
   using type = informationParamParamFactorisation<ReturnType,Args...>;
};

// pointeur de fonction
template < typename ReturnType, typename... Args>
struct informationParam<ReturnType(*)(Args...)>
{
    using type = informationParamParamFactorisation<ReturnType,Args...>;
};

template    <
                class T,
                class U = typename std::enable_if < ! std::is_class<T>::value >::type
            >
informationParam<T> getInformationParam (T t);

template <class T, class U = typename std::enable_if < has_operator_parenthese<T>::value >::type>
informationParam<decltype(&T::operator())> getInformationParam (T t);

template    <
                class T,
                class U = typename std::enable_if <  std::is_class<T>::value >::type,
                class V = typename std::enable_if < !has_operator_parenthese<T>::value >::type
            >
informationParam<T> getInformationParam (T t);


/**
    Les methodes pour l'utilisation simple de ce qu'il y a avant toujours avec 2 ecritures possible

    nbParam(x); // utile pour les lambda et les pointeurs de fonction
    nbParam<X>();//utile pour les classes foncteurs

**/
template<class T>
constexpr size_t nbParam(T fonction)
{
    return decltype(getInformationParam(fonction))::type::arity;
}
template<class T> constexpr size_t nbParam()
{
    return decltype(getInformationParam(std::declval<T>()))::type::arity;
}
template<class T>
using type_nb_param = typename decltype(getInformationParam(std::declval<T>()))::type;


template<size_t nb,class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::type::template arg_type<nb> typeParam(T fonction );

template<size_t nb,class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::type::template arg_type<nb> typeParam();

template<size_t nb,class T>
using type_param = typename decltype(getInformationParam(std::declval<T>()))::type::template arg_type<nb>;

template<class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::type::result_type typeRetour(T fonction );

template<class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::type::result_type typeRetour( );

template <class T>
using type_result = typename decltype(getInformationParam(std::declval<T>()))::type::result_type;
#endif

