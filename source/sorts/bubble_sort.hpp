#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void bubble_sort(Iterator begin, Iterator end, Comporator comp)
{
	bool changed = false;
	do {
		changed = false;
		for(auto i = begin; i + 1 < end; ++i) {
			if(comp(*i, *(i + 1))) {
				std::swap(*i, *(i + 1));
				changed = true;
			}
		}
		--end;
	} while(changed);
}

template<class Iterator>
void bubble_sort(Iterator begin, Iterator end) { bubble_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }