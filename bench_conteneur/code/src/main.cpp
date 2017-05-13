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

#include <array>

#include "lib/fonction_string.hpp"
#include "lib/convertion.hpp"
#include "lib/bench.hpp"
#include "lib/plot.hpp"
#include "lib/outils.hpp"
using namespace libRabbit;

#include "lib/tuple.hpp"

#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
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

template<class T >
void insert_map( size_t taille, const std::vector<size_t>& values)
{
	T conteneur;
	decltype(taille) i = 0;
	for (const auto& v : values)
	{
		conteneur[i] = v;
		++i;
		if ( i >= taille) break;
	}
}



std::vector<size_t> generate_lineaire (size_t max) {
    std::vector<size_t> val;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(i); }
	return val;
}

std::vector<size_t> generate_random (size_t max) {
    std::vector<size_t> val;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(random(size_t(0),max)); }
	return val;
}

template <int max, class T>
void run_bench_insert (std::string nom, T generator)
{
    std::vector<size_t> val = generator(max);
		
	auto plot = make_graphe("vector back",insert<std::vector<size_t>,std::back_insert_iterator>,
                            "vector ",insert<std::vector<size_t>>,
							"list back",insert<std::list<size_t>,std::back_insert_iterator>,
                            "list ",insert<std::list<size_t>>,
                            "unordered_set", insert<std::unordered_set<size_t>>,
                            "set ",insert<std::set<size_t>>,
                            "unordered map", insert_map<std::unordered_map<size_t,size_t>>,
                            "map", insert_map<std::map<size_t,size_t>>);
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i,val);
	}
	
	plot.generate_file("insertion_"+nom,"set logscale y","set key left top");
    
}
int main()
{

    run_bench_insert<10000000>("lineaire",generate_lineaire);
    run_bench_insert<10000000>("random",generate_random);

	
}
