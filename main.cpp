#include <bits/stdc++.h>

#include "sorts.hpp"
#include "TimeTest.hpp"

using testing_signature = std::function<void(std::vector<int>::iterator, std::vector<int>::iterator)>;
using namespace std::literals;

std::tuple<int, int> parse_args(int argc, char** argv)
{
	if(argc != 3)
		throw std::length_error{"Need 2 arguments to start"s};
	return {std::stoul(std::string(argv[1])), std::stoul(std::string(argv[2]))};
}

int main(int argc, char** argv)
{
	unsigned long times, size;
	std::tie(times, size) = parse_args(argc, argv);

	std::array<std::tuple<testing_signature, std::string>, 11> sorts;
	sorts[0] = { std::sort<std::vector<int>::iterator>, "std_sort"s };
	sorts[1] = { bubble_sort<std::vector<int>::iterator>, "bubble_sort"s };
	sorts[2] = { shaker_sort<std::vector<int>::iterator>, "shaker_sort"s };
	sorts[3] = { comb_sort<std::vector<int>::iterator>, "comb_sort"s };
	sorts[4] = { insertion_sort<std::vector<int>::iterator>, "insertion_sort"s };
	sorts[5] = { selection_sort<std::vector<int>::iterator>, "selection_sort"s };
	sorts[6] = { gnome_sort<std::vector<int>::iterator>, "gnome_sort"s };
	sorts[7] = { merge_sort<std::vector<int>::iterator>, "merge_sort"s };
	sorts[8] = { quick_sort<std::vector<int>::iterator>, "quick_sort"s };
	sorts[9] = { lsd_sort<std::vector<int>::iterator>, "lsd_sort"s };
	sorts[10] = { bitonic_sort<std::vector<int>::iterator>, "bitonic_sort"s };

	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::vector<int> vec(size);

	std::cout << "Time testing for sort " << size << " elements " << times << " times" << std::endl;
	for(auto s : sorts) {
		for(auto & i : vec)
			i = generator();
		std::cout << std::get<1>(s) << ": " << TimeTest<testing_signature>(std::get<0>(s), times)(begin(vec), end(vec))
				  << " milliseconds" << std::endl;
	}
	return 0;
}