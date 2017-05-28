#ifndef OUTIL_BENCH_HPP
#define OUTIL_BENCH_HPP
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

namespace libRabbit {


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


	template<class T , class U = void>
	struct has_crochet : public std::false_type {};

	template<class T >
	struct has_crochet<T, void_if_valide_t<decltype(std::declval<T>()[size_t()])> > : public std::true_type {};
	
	
}
#endif // OUTIL_BENCH_HPP
