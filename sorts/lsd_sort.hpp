#pragma once

#include <iterator>
#include <type_traits>
#include <cstring>

template<class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
T digit(T n, T k, T N, T M)
{
	return (n >> (N * k) & (M - 1));
}

template<class Iterator, class = typename std::enable_if<std::is_integral<typename std::iterator_traits<Iterator>::value_type>::value>::type>
void lsd_sort(Iterator begin, Iterator end)
{
	static constexpr auto N = 8;
	static constexpr auto k = (32 + N - 1) / N;
	static constexpr auto M = 1 << N;
	auto dist = std::distance(begin, end);
	auto b = std::make_unique<typename std::iterator_traits<Iterator>::value_type[]>(dist);
	auto c = std::make_unique<typename std::iterator_traits<Iterator>::value_type[]>(M);
	for (auto i = 0; i < k; i++) {
		std::memset(c.get(), 0, M*sizeof(typename std::iterator_traits<Iterator>::value_type));
		for(auto j = begin; j < end; ++j)
			++c[digit(*j, i, N, M)];
		for(auto j = 1; j < M; ++j)
			c[j] += c[j - 1];
		for (auto j = end - 1; j >= begin; --j)
			b[--c[digit(*j, i, N, M)]] = *j;
		std::copy(std::make_move_iterator(b.get()), std::make_move_iterator(&b[dist]), begin);
	}
}