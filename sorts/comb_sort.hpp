#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void comb_sort(Iterator begin, Iterator end, Comporator comp)
{
	static constexpr double k = 1.2473309;
	size_t step = end - begin - 1;
	do {
		for(auto i = begin; i + step < end; ++i)
			if(comp(*i, *(i + 1)))
				std::swap(*i, *(i + 1));
	} while((step /= k) > 1);
	bubble_sort(begin, end, comp);
}

template<class Iterator>
void comb_sort(Iterator begin, Iterator end) { comb_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }