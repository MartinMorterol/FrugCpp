#ifndef CAN_BE_CHECKED
#define CAN_BE_CHECKED

#include <type_traits>
#include <iterator>
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


template <class T, class = void>
struct is_iterator_ : public std::false_type
{
	/// no type
	using no = void;
};

/// @brief Is iterator? (specialization of hopp::is_iterator<T>)
/// @ingroup hopp_type
template <class T>
struct is_iterator_
<
	T,
	typename std::enable_if<std::iterator_traits<T>::value_type>::type
> :
	public std::true_type
{
	/// yes type
	using yes = void;
};



template <class>
struct this_type
{
	/// is_valid type
	using is_valid = void;

	/// is_not_void type
	using is_not_void = void;
};

template <>
struct this_type<void>
{
	/// is_valid type
	using is_valid = int;

	/// is_void type
	using is_void = int;
};


template <bool b>
struct this_expr { };

/// @brief hopp::this_expr<T>::is_true (SFINAE)
/// @ingroup hopp_type
template <>
struct this_expr<true>
{
	/// is_true type
	using is_true = void;
};

/// @brief hopp::this_expr<T>::is_false (SFINAE)
/// @ingroup hopp_type
template <>
struct this_expr<false>
{
	/// is_false type
	using is_false = void;
};

template <class T>
struct void_t

{
	using type =void;
};


template <class T, class U = void >
struct enable_if_ope_parentese : public std::false_type
{
	/// no type
	//using no = void;
	constexpr static bool value2 = false;
};

template <class T>
struct enable_if_ope_parentese
<T, typename this_type<decltype(T()())>::is_valid > // typename std::enable_if<true,decltype(&T::operator())>::type >
//<T, typename void_t<typename std::enable_if<true,decltype(&T::operator())>::type>::type >
	: public std::true_type
{
	/// no type
	using no = void;
	constexpr static bool value2 = true;
};

#endif // CAN_BE_CHECKED
