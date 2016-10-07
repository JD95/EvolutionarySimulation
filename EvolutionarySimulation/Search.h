#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>

template <class T>
std::vector<int> bmh_preprocess( const std::vector<T>& pattern
							   , const int alpha_size)
{
	int pattern_size = pattern.size();

	std::vector<int> table(alpha_size);

	std::fill(table.begin(), table.end(), pattern_size);

	for (int i = 0; i < pattern_size; i++)
		table[pattern[i]] = pattern_size - 1 - i;

	return table;
}

template <class T>
int bmh_search(std::vector<T> needle, std::vector<T> haystack)
{
	return bmh_search(needle, haystack, bmh_preprocess(needle));
}

template <class T>
int bmh_search(std::vector<T> needle, std::vector<T> haystack, std::vector<int> shift_table)
{
	auto increment = [&](int s) { return shift_table[haystack[s + needle.size() - 1]]; };

	for (int skip = 0; haystack.size() - skip >= needle.size(); skip += increment(skip))
	{
		int i = needle.size() - 1;

		for(; haystack[skip + i] == needle[i]; i--)
			if (i == 0)	return skip;			
	}

	return -1;
}
