#pragma once

#include <vector>
#include <utility>

#include "getCPUTime.h"

template<typename target_t>
class TimeTest
{
	target_t target;
	unsigned long long times;
public:
	TimeTest(target_t target, unsigned long long times) : target{target}, times{times} {}
	template<typename ...Args>
	auto operator()(Args&&... args)
	{
		std::vector<double> time_points(times + 1);
		for(auto i = 0; i < times; ++i) {
			time_points[i] = getCPUTime();
			target(std::forward<Args>(args)...);
		}
		time_points[times] = getCPUTime();
		return time_points;
	}
	TimeTest() = delete;
	~TimeTest() = default;
};
