#ifndef VECTOR_BENCH_HPP
#define VECTOR_BENCH_HPP


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
#include <numeric>


namespace libRabbit {

    inline size_t read_for_auto (std::vector<size_t> vec)
	{
		size_t somme = 0;
		for (const auto& elem : vec)
		{
			somme += elem;
		}
		return somme;
	}

	inline size_t read_for_max_out (std::vector<size_t> vec)
	{
		size_t somme = 0;
		size_t max = vec.size();
		for (size_t i = 0 ; i < max ; ++i )
		{
			somme += vec[i];
		}
		return somme;
	}

	inline size_t read_for_max_in (std::vector<size_t> vec)
	{
		size_t somme = 0;
		for (size_t i = 0 ; i < vec.size() ; ++i )
		{
			somme += vec[i];
		}
		return somme;
	}

	inline size_t read_for_at_max_out (std::vector<size_t> vec)
	{
		size_t somme = 0;
		size_t max = vec.size();
		for (size_t i = 0 ; i < max ; ++i )
		{
			somme += vec.at(i);
		}
		return somme;
	}

	inline size_t read_std_for_each (std::vector<size_t> vec)
	{
		size_t somme = 0;
		std::for_each(vec.begin(),vec.end(),[&](size_t elem) { somme += elem ;});
		return somme;
	}

	inline size_t accumulate (std::vector<size_t> vec)
	{
		return std::accumulate(vec.begin(),vec.end(),size_t());
	}

	template <int max>
	void run_vector_bench ()
	{
		
		std::vector<size_t> vec;
		
		auto plot = make_graphe(
			"vector for auto",	[&]() { read_for_auto(vec); },
			"vector for in",	[&]() { read_for_max_in(vec); },
			"vector for out",	[&]() { read_for_max_out(vec); },
			"vector for at out",	[&]() { read_for_at_max_out(vec); },
			"vector std for\\\\_each",	[&]() { read_std_for_each(vec); },
			"vector std accumulate",	[&]() { accumulate(vec); }
		);
		
		for (size_t i = 10 ; i < max ; i*= 10 )
		{
			auto data = generate_lineaire(i);
			charger_data(vec,data);
			plot.run(i);
		}

		cout << plot.data.generate_file("../graphes/vector/lecture_vector_log","set logscale y","set key left top") << " &" << 
				plot.data.generate_file("../graphes/vector/lecture_vector","set key left top") << " & " << endl;

		
	}

}
#endif // INSERTION_BENCH_HPP
