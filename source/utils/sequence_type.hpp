#pragma once 

#include <exception>
#include <string>

using namespace std::literals;

enum class sequence_type {
	random,
	sorted, 
	reversed
};

std::string seqttos(sequence_type type)
{
	switch(type) {
		case sequence_type::random:
			return "random"s;
		case sequence_type::sorted:
			return "sorted"s;
		case sequence_type::reversed:
			return "reversed"s;
		default:
			throw std::invalid_argument{"argument is not a sequence_type variable(seqttos function)"s};
	}
}

