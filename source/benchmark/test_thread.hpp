#pragma once

#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "../utils/sequence_type.hpp"

using testing_signature = std::function<void(std::vector<int>::iterator, std::vector<int>::iterator)>;

void test_thread(const testing_signature sort, const size_t& times, const size_t size,
				const std::string& filename, const sequence_type seq_type) 
{
	auto durations = TimeTest<testing_signature>(sort, times)(size, seq_type);

	std::ofstream out{filename};
	{
		auto tmp_durations = durations;
		auto median = begin(tmp_durations) + tmp_durations.size() / 2;
		std::nth_element(begin(tmp_durations), median, end(tmp_durations));
		out << std::fixed << *median << '\n' << std::endl;
	}


	for(auto duration : durations) {
		out << std::fixed << duration << std::endl;
	}
}
