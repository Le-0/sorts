#pragma once

#include <functional>
#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <algorithm>

using testing_signature = std::function<void(std::vector<int>::iterator, std::vector<int>::iterator)>;

enum class sequence_type {
	random,
	sorted, 
	reversed
};

void test_thread(const testing_signature sort, const unsigned short& times, const unsigned long& size,
				const std::string& filename, const sequence_type seq_type) 
{
	std::ofstream out{filename};
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::vector<int> sequence(size);

	for(auto &elem : sequence)
		elem = generator();
	if(seq_type == sequence_type::sorted)
		std::sort(begin(sequence), end(sequence));
	if(seq_type == sequence_type::reversed)
		std::sort(sequence.rbegin(), sequence.rend());

	std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> time_points;
	time_points = TimeTest<testing_signature>(sort, times)(begin(sequence), end(sequence));

	out << std::chrono::duration_cast<std::chrono::microseconds>(
		(time_points.back() - time_points.front()) / times).count()
		<< '\n' << std::endl;

	for(auto time_point_it = begin(time_points); time_point_it != end(time_points) - 1; ++time_point_it) {
		out << std::chrono::duration_cast<std::chrono::microseconds>(
				*(time_point_it + 1) - *time_point_it).count() << std::endl;
	}

	out.close();
}
