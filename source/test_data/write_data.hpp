#pragma once

#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <thread>
#include "../utils/sequence_type.hpp"

using namespace std::literals;

static void thread_write(std::string destination, sequence_type type) 
{
	std::mt19937 random(std::chrono::system_clock::now().time_since_epoch().count());
	for(size_t i = 0; i < 100; ++i) {
		std::ofstream out(destination + seqttos(type) + "_"s + std::to_string(i));
		switch(type) {
			case sequence_type::random:
				for(size_t i = 0; i < 100000; ++i)
				out << static_cast<int>(random()) << '\n';
				break;
			case sequence_type::sorted:
				{
					std::vector<int> buff_sorted(100000);
					for(auto & elem : buff_sorted)
						elem = random();
					std::sort(begin(buff_sorted), end(buff_sorted));
					for(const auto & elem : buff_sorted)
						out << elem << '\n';
				}
				break;
			case sequence_type::reversed:
				{
					std::vector<int> buff_reversed(100000);
					for(auto & elem : buff_reversed)
						elem = random();
					std::sort(buff_reversed.rbegin(), buff_reversed.rend());
					for(const auto & elem : buff_reversed)
						out << elem << '\n';
				}
				break;
			default:
				throw std::invalid_argument{"argument is not a sequence_type variable(write_data function)"s};
		}
	}

}

void write_data(std::string destination/* path to dir */)
{
	std::vector<std::thread> threads;
	threads.reserve(static_cast<unsigned>(sequence_type::reversed) + 1);
	for(auto i = static_cast<unsigned>(sequence_type::random); i <= static_cast<unsigned>(sequence_type::reversed); ++i) {
		threads.emplace_back(std::thread(thread_write, destination, static_cast<sequence_type>(i)));
	}
	for(auto & thread : threads)
		if(thread.joinable())
			thread.join();
}
