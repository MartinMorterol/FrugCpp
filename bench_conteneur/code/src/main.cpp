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
#include "lecture_bench.hpp"

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


inline void read_for_auto (std::vector<size_t> vec)
{
	size_t somme = 0;
	for (const auto& elem : vec)
	{
		somme += elem;
	}
}

inline void read_for_max_out (std::vector<size_t> vec)
{
	size_t somme = 0;
	size_t max = vec.size();
	for (size_t i = 0 ; i < max ; ++i )
	{
		somme += vec[i];
	}
}

inline void read_for_max_in (std::vector<size_t> vec)
{
	size_t somme = 0;
	for (size_t i = 0 ; i < vec.size() ; ++i )
	{
		somme += vec[i];
	}
}

inline void read_for_at_max_out (std::vector<size_t> vec)
{
	size_t somme = 0;
	size_t max = vec.size();
	for (size_t i = 0 ; i < max ; ++i )
	{
		somme += vec.at(i);
	}
}

template <int max>
	void run_vector_bench (std::string nom)
	{
		
		std::vector<size_t> vec;
		
		


		auto plot = make_graphe(
			"vector for auto",	[&]() { read_for_auto(vec); },
			"vector for in",	[&]() { read_for_max_in(vec); },
			"vector for out",	[&]() { read_for_max_out(vec); },
			"vector for at out",	[&]() { read_for_at_max_out(vec); }
		);
		

		for (size_t i = 10 ; i < max ; i*= 10 )
		{
			auto data = generate_lineaire(i);
			charger_data(vec,data);
			plot.run(i);
		}

		plot.generate_file("insertion_"+nom,"set logscale y","set key left top");
	}


int main()
{


	constexpr size_t max = 10000000;
	run_vector_bench<max> ("lecture");
	/*run_bench_insert<10000000>("lineaire",generate_lineaire);
	run_bench_insert<10000000>("random",generate_random);*/

	
}
