#pragma once

#include <functional>
#include <iterator>
#include <cstring>


template<class Iterator, class Comporator>
void sort_bitonic_sequence(Iterator begin, Iterator end, Comporator comp, bool inv = false)
{
	if(end - begin <= 1) return;
	auto m = begin + (end - begin) / 2;
	for(auto i = begin, j = m; i < m && j < end; ++i, ++j)
		if(inv ^ comp(*i, *j))
			std::swap(*i, *j);
	sort_bitonic_sequence(begin, m, comp, inv);
	sort_bitonic_sequence(m, end, comp, inv);
}


template<class Iterator, class Comporator>
void make_bitonic_sequence(Iterator begin, Iterator end, Comporator comp)
{
	if(end - begin <= 1) return;
	auto m = begin + (end - begin) / 2;
	make_bitonic_sequence(begin, m, comp);
	sort_bitonic_sequence(begin, m, comp);
	make_bitonic_sequence(m, end, comp);
	sort_bitonic_sequence(m, end, comp, true);
}

template<class Iterator, class Comporator>
void bitonic_sort(Iterator begin, Iterator end, Comporator comp)
{
	size_t n = 1;
	auto inf = *max_element(begin, end);
	while(n < end - begin) n *= 2;
	auto a = std::make_unique<typename std::iterator_traits<Iterator>::value_type[]>(n);
	std::copy(begin, end, a.get());
	std::memset(a.get() + static_cast<size_t>(end - begin), inf,
	 (n - static_cast<size_t>(end - begin)) * sizeof(typename std::iterator_traits<Iterator>::value_type));
	make_bitonic_sequence(a.get(), a.get() + n, comp);
	sort_bitonic_sequence(a.get(), a.get() + n, comp);
	std::copy(std::make_move_iterator(a.get()), std::make_move_iterator(&a[end - begin]), begin);
}

template<class Iterator>
void bitonic_sort(Iterator begin, Iterator end) { bitonic_sort(begin, end, std::greater<typename std::iterator_traits<Iterator>::value_type>()); }