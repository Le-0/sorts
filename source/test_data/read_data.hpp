#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../utils/sequence_type.hpp"

using namespace std::literals;

std::vector<int> read_data(std::string destination/* path to dir */, sequence_type type, size_t size, size_t idx/* 0..100 */)
{
	std::ifstream in(destination + seqttos(type) + "_"s + std::to_string(idx));
	std::vector<int> data(size);
	for(auto & elem : data)
		in >> elem;
	return std::move(data);
}
