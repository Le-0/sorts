#pragma once

#include <functional>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

#include "sequence_type.hpp"

using testing_signature = std::function<void(std::vector<int>::iterator, std::vector<int>::iterator)>;

std::vector<double> tptod(std::vector<double> time_points)
{
	std::vector<double> durations(time_points.size() - 1);
	for(int i = 0; i < durations.size(); ++i) {
		durations[i] = (time_points[i + 1] - time_points[i]) * 1000000;	// seconds to mircoseconds
	}
	return durations;
}

void test_thread(const testing_signature sort, const unsigned short& times, const unsigned long& size,
				const std::string& filename, const sequence_type seq_type) 
{
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::vector<int> sequence(size);

	for(auto &elem : sequence)
		elem = generator();
	if(seq_type == sequence_type::sorted)
		std::sort(begin(sequence), end(sequence));
	if(seq_type == sequence_type::reversed)
		std::sort(sequence.rbegin(), sequence.rend());

	auto durations = tptod(TimeTest<testing_signature>(sort, times)(begin(sequence), end(sequence)));

	std::ofstream out{filename};
	{
		auto tmp_durations = durations;
		auto median = begin(tmp_durations) + tmp_durations.size() / 2;
		std::nth_element(begin(tmp_durations), median, end(tmp_durations));
		out << *median << '\n' << std::endl;
	}


	for(auto duration : durations) {
		out << duration << std::endl;
	}
}
