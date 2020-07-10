#pragma once

#include <vector>
#include <utility>
#include <cmath>
#include <string>

#include "../utils/getCPUTime.h"
#include "../utils/sequence_type.hpp"
#include "../test_data/read_data.hpp"

static std::vector<double> convert(const std::vector<std::pair<double, double>>& time_points)
{
	std::vector<double> durations(time_points.size());
	for(size_t i = 0; i < durations.size(); ++i)
		durations[i] = (time_points[i].second - time_points[i].first) * 1000000;
	return durations;
}

template<typename target_t>
class TimeTest
{
	target_t target;
	const size_t times;
public:
	TimeTest(target_t target, const size_t times) : target{target}, times{times} {}
	auto operator()(const size_t size, const sequence_type seq_type)
	{	
		std::vector<int> seq;
		std::vector<std::pair<double, double>> time_points(times);
		for(auto i = 0; i < times; ++i) {
			seq = read_data(std::string("./data/"), seq_type, size, i);

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
