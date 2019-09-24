#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0)
		: theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
	{ objects = new Object[theCapacity]; }

	Vector(const Vector& rhs)
		: theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector& operator= (const Vector& rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector&& rhs)
		: theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector& operator= (Vector&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}

	Object& operator[](int index)
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw ArrayIndexOutOfBoundsException{ };
#endif
		return objects[index];
	}

	const Object& operator[](int index) const
	{
#ifndef NO_CHECK
		if (index < 0 || index >= size())
			throw ArrayIndexOutOfBoundsException{ };
#endif
		return objects[index];
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object* newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	// Stacky stuff
	void push_back(const Object& x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	// Stacky stuff
	void push_back(Object&& x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		if (empty())
			throw UnderflowException{ };
		--theSize;
	}

	const Object& back() const
	{
		if (empty())
			throw UnderflowException{ };
		return objects[theSize - 1];
	}

	// Iterator stuff: not bounds checked
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	/////////////////////////////////////
	// This is added for Project1
	// Pre: This function will be passed an iterator to the element that
	// needs to be removed.
	// Post: This function will remove the desired element.
	void erase(iterator iter)
	{
		// Iterators for the graph
		iterator graphVec = iter;
		iterator graphNext = iter;

		// Move this iterator over one so swapping can happen
		++graphNext;

		// This loop will move the element that needs to be removed
		// to the end of the vector
		while (graphVec != end() && graphNext != end())
		{
			// This block below will do the swap
			Object temp = *graphVec;
			*graphVec = *graphNext;
			*graphNext = temp;

			// Double check that the next position isn't 
			// the end
			if (graphNext != end())
			{
				// Add to the graphNext iterator
				++graphNext;
			}
			
			// Add to the graph iterator
			++graphVec;
		}

		// This will remove the element
		pop_back();

	}

	static const int SPARE_CAPACITY = 2;

private:
	int theSize;
	int theCapacity;
	Object* objects;
};

#endif