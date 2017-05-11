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




template <class ... Even, class ...Odd>
struct test<std::tuple<Even...>,std::tuple<Odd...> >
{
	test()
	{
		cout << "Paire " << endl;
		std::initializer_list<int> r = { (display<Even>(),0)...};
		cout << "Impaire " << endl;
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
	
	std::vector<size_t> val;
	const constexpr size_t max = 10000000;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(i); }

	make_test(1,0.,'e',"1");
	
	auto plot = make_graphe(insert<std::vector<size_t>>,
							insert<std::vector<size_t>,std::back_insert_iterator>);
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i,val);
	}
	
	plot.generate_file("data",{"basique","back"},"set logscale y","set key left top");
	
}
