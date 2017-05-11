#include <utility>
#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <fstream>
#include <vector>
#include <string>
using std::vector;
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>



#include "lib/fonction_string.hpp"
#include "lib/convertion.hpp"
#include "lib/bench.hpp"
#include "lib/plot.hpp"
using namespace libRabbit;

#include "lib/tuple.hpp"

#include <list>
#include <set>


#include <boost/core/demangle.hpp>


template<class T,template <class> class Insert >
void insert ( size_t taille, const std::vector<size_t>& values)
{
	T conteneur;
	Insert<T> ins_it(conteneur);
	decltype(taille) i = 0;
	for (const auto& v : values)
	{
		ins_it = v; 
		++ins_it;
		++i;
		if ( i >= taille) break;
	}
}

template<class T >
void insert ( size_t taille, const std::vector<size_t>& values)
{
	T conteneur;
	std::insert_iterator<T> ins_it(conteneur, conteneur.begin());
	decltype(taille) i = 0;
	for (const auto& v : values)
	{
		ins_it = v; 
		++ins_it;
		++i;
		if ( i >= taille) break;
	}
}


template<class T>
struct nom_fn{
	std::string nom;
	T fn;
	nom_fn(std::string nom_,T&& fn) : nom(nom_), fn(std::forward<T>(fn)) {}
};

template <class... T>
struct test
{
	static_assert(false_<T...>::value,"base");
};


template < class T>
void display  () { std::cout <<boost::core::demangle( typeid(std::decay_t<T>).name()) << std::endl; }

template < int i, class T>
void display  (T&& t) { std::cout << std::get<i>(t) << std::endl; }

template < size_t ...I, class T>
void display_tuple_impl(std::index_sequence<I...>,T&& t) {
	std::initializer_list<int> r = { (display<I>(t),0)...};
}


template < class T>
void display_tuple (T t) {
	display_tuple_impl( get_indexes(t) , t);
}


template <int i, int j = i%2>
struct is_even {
	constexpr static const bool value = false;
};
template <int i>
struct is_even<i,0> {
	constexpr static const bool value = true;
};

template <int i, int j = i%2>
struct is_odd {
	constexpr static const bool value = false;
};
template <int i>
struct is_odd<i,1> {
	constexpr static const bool value = true;
};

template<bool go, int i , class TupleCible, class Value>
struct add_tuple ;

template<int i , class TupleCible, class Value>
struct add_tuple<false,i,TupleCible,Value> {
	static void add (TupleCible& t, Value v)
	{
		
	}
};

template<int i , class TupleCible, class Value>
struct add_tuple  <true,i,TupleCible,Value> {
	static void add (TupleCible& t,Value v)
	{
		std::get<i/2>(t) = v;
	}
};



template < size_t ...I ,class Tuple, class ... Args>
void make_tuple_even_impl(std::index_sequence<I...>,Tuple& t, Args... args) {
	std::initializer_list<int> r = {  (add_tuple< is_even<I>::value,I,std::decay_t<Tuple>,std::decay_t<Args>>::add(t,args),0)...};
}

/***
 *  Je ne comprend pas pourquoi je n'arrive pas passer is_even tant que selecteur template
 *  a make_tuple_even_impl
 */
template <class... T>
even_tuple_t<T...> make_tuple_even (T... t) {
	even_tuple_t<T...> retour;
	make_tuple_even_impl( std::make_index_sequence<sizeof...(T)>(), retour, t... );
	return retour;
}

template <class ... Even, class ...Odd>
struct test<std::tuple<Even...>,std::tuple<Odd...> >
{
	std::tuple<Even...> e;
	std::tuple<Odd...> o;
	test()
	{	cout << "Paire ! " << endl;
		display_tuple(e);
		cout << "Impaire!!" << endl;
		display_tuple(o);
		cout<< endl<< endl << "Paire !!!!" << endl;
		std::initializer_list<int> r = { (display<Even>(),0)...};
		cout << "Impaire !!!!!!!" << endl;
		std::initializer_list<int> rr = { (display<Odd>(),0)...};
	}
};

template <class ... T>
auto make_test (T ... params)
{
	test< 	typename even_tuple<T...>::type ,
			typename odd_tuple<T...>::type
		> d;
}




template <class U, class V, class ... W >
auto make_pair_ (U&& u, V&& v, W...)  { return std::make_pair(std::forward<U>(u),std::forward<V>(v)); }







int main()//int argc, char** argv)
{
	
	//cout << is_even<4>::value << endl;
	
	auto t = make_tuple_even(1,2.,'v',short(1));
	display_tuple(t);
	/*
	std::vector<size_t> val;
	const constexpr size_t max = 10000000;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(i); }

	cout << "lapin" << endl;
	make_test(1,0.,'e',"1");
	/*
	auto plot = make_graphe(insert<std::vector<size_t>>,
							insert<std::vector<size_t>,std::back_insert_iterator>);
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i,val);
	}
	
	plot.generate_file("data",{"basique","back"},"set logscale y","set key left top");
	*/
}
