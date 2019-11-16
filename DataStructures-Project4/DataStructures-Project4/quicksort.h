// Nathaniel Shetler
// Code from Data Structures and Algorithm Analysis in C++ (Fourth Edition), by Mark Allen Weiss
#ifndef QUICK_H
#define QUICK_H

#include <vector>
#include <functional>
using namespace std;

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right)
{
	int center = (left + right) / 2;

	if (a[center] < a[left])
		std::swap(a[left], a[center]);
	if (a[right] < a[left])
		std::swap(a[left], a[right]);
	if (a[right] < a[center])
		std::swap(a[center], a[right]);

	// Place pivot at position right - 1
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}

// New quicksort (no cutoff)
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right)
{
	// A boolean for the loop
	bool done = false;

	// If the size of the array is less than 2
	if ((right - left) < 2)
	{
		// If they are out of order, swap them
		if (a[right] < a[left])
		{
			std::swap(a[left], a[right]);
		}
	}
	else if (left < right) // This block will do the big sorting
	{
		// These are the i and j values discussed in class
		int i = left, j = right - 1;

		// Get the pivot using median3
		const Comparable& pivot = median3(a, left, right); 

		// Loop for sorting
		while (!done)
		{
			// Find first value on the left that's greater than the pivot
			while (a[++i] < pivot)
			{
				// i will be set after the value that is greater than pivot is found
			}

			// Find the first value on the right that's less than the pivot
			while (pivot < a[--j])
			{
				// j will be set after the value that is less than pivot is found
			}

			// If i is less than j then swap the two 
			if (i < j)
			{
				std::swap(a[i], a[j]);
			}
			else
			{
				// Otherwise, we are done with this section
				done = true;
			}
		}

		// Put the pivot back in the correct place
		std::swap(a[i], a[right - 1]);

		// Do the same thing recursively for both sides
		quicksort(a, left, i - 1);
		quicksort(a, i + 1, right);
	}
	else
	{
		// If all else is done, return (may not need)
		return;
	}
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
	quicksort(a, 0, a.size() - 1);
}

#endif