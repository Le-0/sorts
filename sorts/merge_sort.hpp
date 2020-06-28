#pragma once

#include <functional>
#include <iterator>

template<class Iterator, class Comporator>
void merge_sort(Iterator begin, Iterator end, Comporator comp)
{
	auto dist = std::distance(begin, end);
	if(dist > 1) {
		merge_sort(begin, begin + dist / 2, comp);
		merge_sort(begin + dist / 2, end, comp);

		auto tmp = std::make_unique<typename std::iterator_traits<Iterator>::value_type[]>(dist);
		auto cur = tmp.get();
		auto l = begin;
		auto r = begin + dist / 2;

		while(l < begin + dist / 2 && r < end) {
			*cur++ = comp(*l, *r) ? std::move(*r++) : std::move(*l++);
		}
		std::copy(std::make_move_iterator(l), std::make_move_iterator(begin + dist / 2), cur);
		std::copy(std::make_move_iterator(r), std::make_move_iterator(end), cur);
		std::copy(std::make_move_iterator(tmp.get()), std::make_move_iterator(&tmp[dist]), begin);
	}
}

template<class Iterator>
void merge_sort(Iterator begin, Iterator end) { merge_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }