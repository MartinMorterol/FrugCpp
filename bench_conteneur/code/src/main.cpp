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
#include "vector_bench.hpp"
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
#include <numeric>
#include <cstring>

int main()
{


	constexpr size_t max = 100000000;
	//run_vector_bench<max> ();
	run_bench_insert_vector<max>("lineaire",generate_lineaire);
	//run_bench_insert<max>("lineaire",generate_lineaire);
 	//run_bench_insert<max>("random",generate_random);*
	
	

	
}
