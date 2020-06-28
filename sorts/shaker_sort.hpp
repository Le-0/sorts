#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void shaker_sort(Iterator begin, Iterator end, Comporator comp)
{
	bool changed = false;
	auto l = begin - 1, r = end - 1;
	do {
		changed = false;
		++l;
		for(auto i = l; i < r; ++i) {
			if(comp(*i, *(i + 1))) {
				std::swap(*i, *(i + 1));
				changed = true;
			}
		}
		if(!changed) break;
		--r;
		for(auto i = r; i > l; --i) {
			if(!comp(*i, *(i - 1))) {
				std::swap(*i, *(i - 1));
				changed = true;
			}
		}
	} while(changed);
}

template<class Iterator>
void shaker_sort(Iterator begin, Iterator end) { shaker_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }