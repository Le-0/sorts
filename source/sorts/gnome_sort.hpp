#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void gnome_sort(Iterator begin, Iterator end, Comporator comp)
{
	auto i = begin;
	while(i < end) {
		if(i == begin || !comp(*(i - 1), *i)) {
			++i;
		} else {
			std::swap(*(i - 1), *i);
			--i;
		}
	}
}

template<class Iterator>
void gnome_sort(Iterator begin, Iterator end) { gnome_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }