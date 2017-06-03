#ifndef LECTURE_BENCH_HPP
#define LECTURE_BENCH_HPP


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

#include "outil_bench.hpp"
namespace libRabbit {

	template <bool,class T>
	struct read_impl
	{
		static void read(const T& conteneur, size_t taille)
		{
			size_t cpt = 0;
			size_t somme = 0 ;
			std::vector<size_t> vec;
			vec.reserve(taille);
			for (const auto& elem : conteneur )
			{
				//vec.push_back(elem);
				somme += elem;
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
			//std::vector<size_t> vec;
			// vec.reserve(taille);
			size_t somme = 0;
			size_t max = std::min(taille,conteneur.size());
			for (size_t i = 0 ; i < max  ; ++i )
			{
				//somme += conteneur.at(i);
				somme += conteneur[i];
				//vec.push_back(conteneur.at(i));
			}
		}
	};


	template <class T>
	void read(const T& conteneur, size_t taille)
	{
		read_impl<has_crochet<T>::value,T>::read(conteneur,taille);
	}


	template <int max>
	void run_bench_read (std::string nom)
	{
		auto data = generate_lineaire(max);
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
			"vector",	[&](size_t taille) { read(vec,taille); }
		
		);
		/*
		* 
		*  "un set",	[&](size_t taille) { read(un_set,taille); },
			"set",	[&](size_t taille) { read(set,taille); },
			"un map",	[&](size_t taille) { read(un_map,taille); },
			"map",	[&](size_t taille) { read(map,taille); }*/

		for (size_t i = 10 ; i < max ; i*= 10 )
		{
			plot.run(i,i);
		}

		plot.generate_file("insertion_"+nom,"set logscale y","set key left top");
	}
}
#endif // INSERTION_BENCH_HPP
