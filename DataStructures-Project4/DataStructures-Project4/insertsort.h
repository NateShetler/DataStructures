// Nathaniel Shetler
// Code from Data Structures and Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
#ifndef INSERTION_H
#define INSERTION_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */

#include <vector>
#include <functional>
using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort(vector<Comparable>& a)
{
	for (int p = 1; p < a.size(); ++p)
	{
		Comparable tmp = std::move(a[p]);

		int j;
		for (j = p; j > 0 && tmp < a[j - 1]; --j)
			a[j] = std::move(a[j - 1]);
		a[j] = std::move(tmp);
	}
}

/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
	for (int p = left + 1; p <= right; ++p)
	{
		Comparable tmp = std::move(a[p]);
		int j;

		for (j = p; j > left && tmp < a[j - 1]; --j)
			a[j] = std::move(a[j - 1]);
		a[j] = std::move(tmp);
	}
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename RandomIterator, typename Comparator>
void insertionSort(const RandomIterator& begin,
	const RandomIterator& end,
	Comparator lessThan)
{
	if (begin == end)
		return;

	RandomIterator j;

	for (RandomIterator p = begin + 1; p != end; ++p)
	{
		auto tmp = std::move(*p);
		for (j = p; j != begin && lessThan(tmp, *(j - 1)); --j)
			* j = std::move(*(j - 1));
		*j = std::move(tmp);
	}
}

/*
 * The two-parameter version calls the three parameter version, using C++11 decltype
 */
template <typename RandomIterator>
void insertionSort(const RandomIterator& begin,
	const RandomIterator& end)
{
	insertionSort(begin, end, less<decltype(*begin)>{ });
}

#endif