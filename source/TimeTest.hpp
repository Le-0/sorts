#pragma once

#include <vector>
#include <utility>
#include <random>
#include <chrono>

#include "getCPUTime.h"
#include "sequence_type.hpp"

template<typename target_t, typename sequence_t>
class TimeTest
{
	target_t target;
	unsigned long long times;
public:
	TimeTest(target_t target, unsigned long long times) : target{target}, times{times} {}
	auto operator()(const size_t size, const sequence_type seq_type)
	{
		sequence_t seq(size);
		std::vector<double> time_points(times * 2);
		std::mt19937 random(std::chrono::system_clock::now().time_since_epoch().count());
		for(auto i = 0; i < times * 2; i += 2) {
			for(auto &elem : seq)
				elem = random();
			if(seq_type == sequence_type::sorted)
				std::sort(std::begin(seq), std::end(seq));
			if(seq_type == sequence_type::reversed)
				std::sort(seq.rbegin(), seq.rend());

			time_points[i] = getCPUTime();
			target(std::begin(seq), std::end(seq));
			time_points[i + 1] = getCPUTime();

			seq.clear();
		}
		return time_points;
	}
	TimeTest() = delete;
	~TimeTest() = default;
};
