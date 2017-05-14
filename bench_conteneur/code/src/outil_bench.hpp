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
}
#endif // OUTIL_BENCH_HPP
