#include <utility>
#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <fstream>
#include <vector>
#include <string>
using std::vector;


#include <array>

#include "lib/fonction_string.hpp"
#include "lib/convertion.hpp"
#include "lib/bench.hpp"
#include "lib/plot.hpp"
#include "lib/outils.hpp"
using namespace libRabbit;

#include "lib/tuple.hpp"
#include "insertion_bench.hpp"
#include "outil_bench.hpp"
#include <boost/core/demangle.hpp>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>

template<class	T>
void charger_data (T& conteneur, decltype(generate_lineaire(1))& data)
{
	std::copy(data.begin(), data.end(), std::inserter(conteneur,conteneur.begin()));
}

template<>
void charger_data<std::map<size_t,size_t>> (std::map<size_t,size_t>& conteneur, decltype(generate_lineaire(1))& data)
{
	for (auto i : data) { conteneur[i] = i ;}
}
template<>
void charger_data<std::unordered_map<size_t,size_t>> (std::unordered_map<size_t,size_t>& conteneur, decltype(generate_lineaire(1))& data)
{
	for (auto i : data) { conteneur[i] = i ;}
}

template<class T , class U = void>
struct has_at : public std::false_type {};

template<class T >
struct has_at<T, void_if_valide_t<decltype(std::declval<T>().at(size_t()))> > : public std::true_type {};

template <bool,class T>
struct read_impl
{
	static void read(const T& conteneur, size_t taille)
	{
		size_t cpt = 0;
		std::vector<size_t> vec;
		vec.reserve(taille);
		for (const auto& elem : conteneur )
		{
			vec.push_back(elem);
			if ( ++cpt >= taille) {
				break;
			}
		}
	}
};

template <class T>
struct read_impl<true, T>
{
	static void read(const T& conteneur, size_t taille)
	{
		std::vector<size_t> vec;
		vec.reserve(taille);
		for (size_t i = 0 ; i < std::min(taille,conteneur.size()) ; ++i )
		{
			vec.push_back(conteneur.at(i));
		}
	}
};


template <class T>
void read(const T& conteneur, size_t taille)
{
	read_impl<has_at<T>::value,T>::read(conteneur,taille);
}


template <int max>
void run_bench_read (std::string nom)
{
	auto data = generate_lineaire(10000000);
	std::vector<size_t> vec;
	std::list<size_t> list;
	std::set<size_t> set;
	std::map<size_t,size_t> map;
	std::unordered_set<size_t> un_set;
	std::unordered_map<size_t,size_t> un_map;

	charger_data(vec,data);
	charger_data(list,data);
	charger_data(set,data);
	charger_data(map,data);
	charger_data(un_set,data);
	charger_data(un_map,data);


	auto plot = make_graphe(
	    "list",		[&](size_t taille) { read(list,taille); },
	    "vector",	[&](size_t taille) { read(vec,taille); },
	    "un set",	[&](size_t taille) { read(un_set,taille); },
	    "set",	[&](size_t taille) { read(set,taille); },
	    "un map",	[&](size_t taille) { read(un_map,taille); },
	    "map",	[&](size_t taille) { read(map,taille); }
	);

	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i);
	}

	plot.generate_file("insertion_"+nom,"set logscale y","set key left top");
}


int main()
{


	constexpr size_t max = 10000000;
	run_bench_read<max> ("lecture");
	/*run_bench_insert<10000000>("lineaire",generate_lineaire);
	run_bench_insert<10000000>("random",generate_random);*/

	
}
