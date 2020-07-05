#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void quick_sort(Iterator begin, Iterator end, Comporator comp)
{
	auto z = *(begin + (end - begin) / 2);
	auto l = begin;
	auto r = end - 1;
	while(l <= r) {
		while(*l < z) ++l;
		while(*r > z) --r;
		if(l <= r) {
			std::swap(*l, *r);
			++l;
			--r;
		}
	}
	if(begin < r) quick_sort(begin, r + 1, comp);
	if(l < end) quick_sort(l, end, comp);
}

template<class Iterator>
void quick_sort(Iterator begin, Iterator end) { quick_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }