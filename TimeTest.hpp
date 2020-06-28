#pragma once

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
		auto start = std::chrono::high_resolution_clock::now();
		for(auto i = 0; i < times; ++i) {
			target(std::forward<Args>(args)...);
		}
		return std::chrono::duration_cast<std::chrono::milliseconds>(
			(std::chrono::high_resolution_clock::now() - start) / times
			).count();
	}
	TimeTest() = delete;
	~TimeTest() = default;
};