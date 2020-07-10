#pragma once

#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include <utility>
#include <cmath>

#include "../utils/getCPUTime.h"
#include "../utils/sequence_type.hpp"

static std::vector<double> convert(const std::vector<std::pair<double, double>>& time_points)
{
	std::vector<double> durations(time_points.size());
	for(size_t i = 0; i < durations.size(); ++i)
		durations[i] = (time_points[i].second - time_points[i].first) * 1000000;
	return durations;
}

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
		std::vector<std::pair<double, double>> time_points(times);
		std::mt19937 random(std::chrono::system_clock::now().time_since_epoch().count());
		for(auto i = 0; i < times; ++i) {
			for(auto &elem : seq)
				elem = random();
			if(seq_type == sequence_type::sorted)
				std::sort(std::begin(seq), std::end(seq));
			if(seq_type == sequence_type::reversed)
				std::sort(seq.rbegin(), seq.rend());

			time_points[i].first = getCPUTime();
			target(std::begin(seq), std::end(seq));
			time_points[i].second = getCPUTime();

			seq.clear();
		}
		return convert(time_points);
	}
	TimeTest() = delete;
	~TimeTest() = default;
};
