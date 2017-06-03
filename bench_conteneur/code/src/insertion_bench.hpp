#ifndef INSERTION_BENCH_HPP
#define INSERTION_BENCH_HPP


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
#include <cstring>
#include "outil_bench.hpp"
namespace libRabbit {

	
	void insert_vector_mem( size_t taille, const std::vector<size_t>& values)
	{
		std::vector<size_t> copy(taille);
		std::memcpy(&(copy[0]), &(values[0]), taille * sizeof(size_t));
	}
	
	void insert_vector_assing( size_t taille, const std::vector<size_t>& values)
	{
		std::vector<size_t> copy;
		copy.assign(values.begin(),values.begin()+(int)taille); // mute warning
	}
	
	void insert_vector_insert( size_t taille, const std::vector<size_t>& values)
	{
		std::vector<size_t> copy;
		copy.insert(copy.begin(),values.begin(),values.begin()+(int)taille); // mute warning
	}
	
	
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

	template <int max, class T>
	void run_bench_insert_vector(std::string nom, T generator)
	{
		std::vector<size_t> val = generator(max);

		auto plot = make_graphe(
								"vector insert", insert_vector_insert,
								"vector memcpy", insert_vector_mem,
								"vector assign", insert_vector_assing,
								"vector back",insert<std::vector<size_t>,std::back_insert_iterator>,
		                        "vector insert iterator",insert<std::vector<size_t>>
								
   							);
		for (size_t i = 10 ; i < max ; i*= 10 )
		{
			plot.run(i,i,val);
		}
		

		cout << plot.data.generate_file("../graphes/insert/insert_vector"+nom+"_log","set logscale y","set key left top") << " &" << 
				plot.data.generate_file("../graphes/insert/insert_vector"+nom,"set key left top") << " & " << endl;


	}
	
	template <int max, class T>
	void run_bench_insert (std::string nom, T generator)
	{
		std::vector<size_t> val = generator(max);

		auto plot = make_graphe(
								"vector memcpy", insert_vector_mem,
								"vector back",insert<std::vector<size_t>,std::back_insert_iterator>,
		                        "vector ",insert<std::vector<size_t>>,
								"vector insert", insert_vector_insert,
								"vector assign", insert_vector_assing,
		                        "list back",insert<std::list<size_t>,std::back_insert_iterator>,
		                        "list ",insert<std::list<size_t>>,
		                        "unordered\\\\_set", insert<std::unordered_set<size_t>>,
		                        "set ",insert<std::set<size_t>>,
		                        "map", insert_map<std::map<size_t,size_t>>,
								"unordered\\\\_map", insert_map<std::unordered_map<size_t,size_t>>
   							);
		for (size_t i = 10 ; i < max ; i*= 10 )
		{
			plot.run(i,i,val);
		}
		

		cout << plot.data.generate_file("../graphes/insert/insert_"+nom+"_log","set logscale y","set key left top") << " &" << 
				plot.data.generate_file("../graphes/insert/insert_"+nom,"set key left top") << " & " << endl;


	}
}
#endif // INSERTION_BENCH_HPP
