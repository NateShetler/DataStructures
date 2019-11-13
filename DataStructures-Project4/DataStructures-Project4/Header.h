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

#endif