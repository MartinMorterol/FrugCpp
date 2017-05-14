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
template <class T>
void read(const T& conteneur, size_t taille)
{
	for (size_t i = 0 ; i < std::min(taille,conteneur.size()) ; ++i )
	{
		auto result = conteneur[i];
		(void) result;
	}
}

template <int max>
void run_bench_read (std::string nom)
{
	auto data = generate_lineaire(10000000);
	std::vector<size_t> vec;
	std::list<size_t> list;

	charger_data(vec,data);
	charger_data(list,data);

	/*auto plot = make_graphe("vector",	[&](size_t taille) { read(vec,taille); } ,
							"list",		[&](size_t taille) { read(list,taille); });
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i);
	}

	plot.generate_file("insertion_"+nom,"set logscale y","set key left top");*/
}

template < size_t... I, class T, class Add >
auto test_impl(std::index_sequence<I...>, T&& tuple, Add&& a) {
	return std::make_tuple(std::get<I>(tuple)...,std::forward<Add>(a));
}


template<class T, class Add>
auto test (T&& tuple, Add&& a)
{
	return test_impl(get_indexes(tuple), std::forward<T>(tuple) , std::forward<Add>(a) );
}

int main()
{
	std::vector<size_t> vec;
	std::list<size_t> list;
	auto tuple1 = std::make_tuple([&](size_t taille) { read(vec,taille);});
	auto tuple = test (tuple1,[&](size_t taille) { read(vec,taille); }) ;
	//display_tuple(tuple);
	std::get<0>(tuple)(5);
	std::get<1>(tuple)(5);
	constexpr size_t max = 10000000;
	run_bench_read<max> ("lecture");
	/*run_bench_insert<10000000>("lineaire",generate_lineaire);
	run_bench_insert<10000000>("random",generate_random);*/

	
}
