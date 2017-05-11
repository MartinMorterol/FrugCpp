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



int main()
{
	


	std::vector<size_t> val;
	const constexpr size_t max = 10000000;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(i); }

	auto plot = make_graphe("basique !",insert<std::vector<size_t>>,
							"back",insert<std::vector<size_t>,std::back_insert_iterator>);
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i,val);
	}
	
	plot.generate_file("data","set logscale y","set key left top");

}
