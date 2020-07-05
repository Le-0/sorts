#pragma once

#include <vector>
#include <utility>
#include <chrono>

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
		std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> time_points(times + 1);
		for(auto i = 0; i < times; ++i) {
			time_points[i] = std::chrono::high_resolution_clock::now();
			target(std::forward<Args>(args)...);
		}
		time_points[times] = std::chrono::high_resolution_clock::now();
		return time_points;
	}
	TimeTest() = delete;
	~TimeTest() = default;
};