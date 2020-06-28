#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void selection_sort(Iterator begin, Iterator end, Comporator comp)
{
	for(auto i = begin; i < end; ++i) {
		auto min = *i;
		auto idx = i;
		for(auto j = i + 1; j < end; ++j) {
			if(!comp(*j, min)) {
				min = *j;
				idx = j;
			}
		}
		std::swap(*i, *idx);
	}
}

template<class Iterator>
void selection_sort(Iterator begin, Iterator end) { selection_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }