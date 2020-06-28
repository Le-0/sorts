#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void insertion_sort(Iterator begin, Iterator end, Comporator comp)
{
	for(auto i = begin + 1; i < end; ++i) {
		auto j = i;
		while(j > begin && comp(*(j - 1), *j)) {
			std::swap(*j, *(j - 1));
			--j;
		}
	}
}

template<class Iterator>
void insertion_sort(Iterator begin, Iterator end) { insertion_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }