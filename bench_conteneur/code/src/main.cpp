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



#include <list>
#include <set>


int main()//int argc, char** argv)
{
	auto clear = [](auto ...conteur)
	{
		std::initializer_list<int> trick = { ( (conteur.clear()),0)... };
		(void)trick;
	};
	auto insert = [](auto conteneur, auto taille, const auto& values){
		  std::insert_iterator<decltype(conteneur)> ins_it(conteneur, conteneur.begin());
		  decltype(taille) i = 0;
		  for (const auto& v : values)
		  {
			  ins_it = v; 
			  ++ins_it;
			  ++i;
			  if ( i >= taille) break;
		  }
	};
	
	std::vector<size_t> v;
	std::list<size_t> l;
	std::set<size_t> s;
	
	std::vector<size_t> val;
	const constexpr size_t max = 10000000;
	for (size_t i = 0 ; i < max ; ++i) { val.push_back(i); }
	
	auto insert_v = [&](size_t taille) { insert(v,taille,val); };
	auto insert_l = [&](size_t taille) { insert(l,taille,val); };
	auto insert_s = [&](size_t taille) { insert(s,taille,val); };

	
	auto plot = make_graphe(insert_v,insert_l,insert_s);
	for (size_t i = 10 ; i < max ; i*= 10 )
	{
		plot.run(i,i);
		clear(v,l,s);
	}
	
	plot.generate_file("data",{"vector","list","set"},"set logscale y","set key left top");

	
}
