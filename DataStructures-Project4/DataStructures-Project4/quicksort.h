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

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a, int left, int right)
{
	if (left + 10 <= right)
	{
		const Comparable& pivot = median3(a, left, right);

		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}

		std::swap(a[i], a[right - 1]);  // Restore pivot

		quicksort(a, left, i - 1);     // Sort small elements
		quicksort(a, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

/**
 * Quicksort algorithm (driver).
 */
template <typename Comparable>
void quicksort(vector<Comparable>& a)
{
	quicksort(a, 0, a.size() - 1);
}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int left, int right, int k)
{
	if (left + 10 <= right)
	{
		const Comparable& pivot = median3(a, left, right);

		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}

		std::swap(a[i], a[right - 1]);  // Restore pivot

			// Recurse; only this part changes
		if (k <= i)
			quickSelect(a, left, i - 1, k);
		else if (k > i + 1)
			quickSelect(a, i + 1, right, k);
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect(vector<Comparable>& a, int k)
{
	quickSelect(a, 0, a.size() - 1, k);
}


template <typename Comparable>
void SORT(vector<Comparable>& items)
{
	if (items.size() > 1)
	{
		vector<Comparable> smaller;
		vector<Comparable> same;
		vector<Comparable> larger;

		auto chosenItem = items[items.size() / 2];

		for (auto& i : items)
		{
			if (i < chosenItem)
				smaller.push_back(std::move(i));
			else if (chosenItem < i)
				larger.push_back(std::move(i));
			else
				same.push_back(std::move(i));
		}

		SORT(smaller);     // Recursive call!
		SORT(larger);      // Recursive call!

		std::move(begin(smaller), end(smaller), begin(items));
		std::move(begin(same), end(same), begin(items) + smaller.size());
		std::move(begin(larger), end(larger), end(items) - larger.size());

		/*
				items.clear( );
				items.insert( end( items ), begin( smaller ), end( smaller ) );
				items.insert( end( items ), begin( same ), end( same ) );
				items.insert( end( items ), begin( larger ), end( larger ) );
		*/
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

#endif