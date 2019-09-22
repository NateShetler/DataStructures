#ifndef LIST_H
#define LIST_H

#include <algorithm>

// Mark Weiss List template class

using namespace std;

template <typename Object>
class List
{
private:
	// The basic doubly linked list node.
	// Nested inside of List, can be public
	// because the Node is itself private
	struct Node
	{
		Object  data;
		Node* prev;
		Node* next;

		Node(const Object& d = Object{ }, Node* p = nullptr, Node* n = nullptr)
			: data{ d }, prev{ p }, next{ n } { }

		Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
			: data{ std::move(d) }, prev{ p }, next{ n } { }
	};

public:
	class const_iterator
	{
	public:

		// Public constructor for const_iterator.
		const_iterator() : current{ nullptr }
		{ }

		// Return the object stored at the current position.
		// For const_iterator, this is an accessor with a
		// const reference return type.
		const Object& operator* () const
		{
			return retrieve();
		}

		const_iterator& operator++ ()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		const_iterator& operator-- ()
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator-- (int)
		{
			const_iterator old = *this;
			--(*this);
			return old;
		}

		bool operator== (const const_iterator& rhs) const
		{
			return current == rhs.current;
		}

		bool operator!= (const const_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Node* current;

		// Protected helper in const_iterator that returns the object
		// stored at the current position. Can be called by all
		// three versions of operator* without any type conversions.
		Object& retrieve() const
		{
			return current->data;
		}

		// Protected constructor for const_iterator.
		// Expects a pointer that represents the current position.
		const_iterator(Node* p) : current{ p }
		{ }

		friend class List<Object>;
	};

	class iterator : public const_iterator
	{
	public:

		// Public constructor for iterator.
		// Calls the base-class constructor.
		// Must be provided because the private constructor
		// is written; otherwise zero-parameter constructor
		// would be disabled.
		iterator()
		{ }

		Object& operator* ()
		{
			return const_iterator::retrieve();
		}

		// Return the object stored at the current position.
		// For iterator, there is an accessor with a
		// const reference return type and a mutator with
		// a reference return type. The accessor is shown first.
		const Object& operator* () const
		{
			return const_iterator::operator*();
		}

		iterator& operator++ ()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		iterator& operator-- ()
		{
			this->current = this->current->prev;
			return *this;
		}

		iterator operator-- (int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

	protected:
		// Protected constructor for iterator.
		// Expects the current position.
		iterator(Node* p) : const_iterator{ p }
		{ }

		friend class List<Object>;
	};

public:
	List()
	{
		init();
	}

	~List()
	{
		clear();
		delete head;
		delete tail;
	}

	List(const List& rhs)
	{
		init();
		for (auto& x : rhs)
			push_back(x);
	}

	List& operator= (const List& rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}


	List(List&& rhs)
		: theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	List& operator= (List&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);

		return *this;
	}

	// Return iterator representing beginning of list.
	// Mutator version is first, then accessor version.
	iterator begin()
	{
		return iterator(head->next);
	}

	const_iterator begin() const
	{
		return const_iterator(head->next);
	}

	// Return iterator representing endmarker of list.
	// Mutator version is first, then accessor version.
	iterator end()
	{
		return iterator(tail);
	}

	const_iterator end() const
	{
		return const_iterator(tail);
	}

	// Return number of elements currently in the list.
	int size() const
	{
		return theSize;
	}

	// Return true if the list is empty, false otherwise.
	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	// front, back, push_front, push_back, pop_front, and pop_back
	// are the basic double-ended queue operations.
	Object& front()
	{
		return *begin();
	}

	const Object& front() const
	{
		return *begin();
	}

	Object& back()
	{
		return *--end();
	}

	const Object& back() const
	{
		return *--end();
	}

	void push_front(const Object& x)
	{
		insert(begin(), x);
	}

	void push_back(const Object& x)
	{
		insert(end(), x);
	}

	void push_front(Object&& x)
	{
		insert(begin(), std::move(x));
	}

	void push_back(Object&& x)
	{
		insert(end(), std::move(x));
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	// Insert x before itr.
	iterator insert(iterator itr, const Object& x)
	{
		Node* p = itr.current;
		++theSize;
		return iterator(p->prev = p->prev->next = new Node{ x, p->prev, p });
	}

	// Insert x before itr.
	iterator insert(iterator itr, Object&& x)
	{
		Node* p = itr.current;
		++theSize;
		return iterator(p->prev = p->prev->next = new Node{ std::move(x), p->prev, p });
	}

	// Erase item at itr.
	iterator erase(iterator itr)
	{
		Node* p = itr.current;
		iterator retVal(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		--theSize;

		return retVal;
	}

	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to; )
			itr = erase(itr);

		return to;
	}

	/////////////////////////////////////////////////////////////////////////////
	// This is added for Project1 
	// Precondtion: This function will accept iterators for the list and also the data that it is 
	// looking for.
	// Postcondition: The function will return an iterator to the location before the data that is being
	// searched for
	iterator find_gt(iterator begin, iterator end, Object data)
	{
		// Go through the list and check if the data in the list is bigger than
		// what the user entered

		// Note to self: could also make this a while loop
		for (; begin != end; ++begin)
		{
			if (*begin > data)
			{
				return begin;
			}
		}

		// If it's not anywhere in the middle then return end
		return end;
	}

	/////////////////////////////////////////////////////////////////////////////
	// This is added for Project1
	// Precondition: This will accept in a list
	// Postcondition: This will check to see if there are any common elements and if there are then
	// it will return true, it will return false otherwise.
	bool commonElement(List <Object>& comp)
	{
		// For deciding which list is bigger.
		int bigger = 0;

		// Setting bigger based on the size of the lists
		if (size() > comp.size())
		{
			bigger = size();
		}
		else
		{
			bigger = comp.size();
		}

		// Going through the lists and finding common elements
		for (int i = 0; i < bigger; ++i)
		{
			iterator list1 = comp.begin();
			iterator list2 = begin();

			if (*list1 == *list2)
			{
				return true;
			}
			else 
			{
				++list1;
				++list2;
			}
		}

		return false;
	}	///////////////////////////////////////////////////////////////
	// This function was added for Project1
	// Pre condition is that rhs is the smaller of the two lists
	// Post condition is that the two lists are merged. The function
	// merges the two lists
	void mergeNoDups(const List<Object>& rhs)
	{
		// Iterators to go through the lists
		List<Object>::const_iterator smallList = rhs.begin();
		List<Object>::iterator insertPlace;
		List<Object>::const_iterator insertPlaceNext;

		// This will go through small list and insert the values if necessary
		while (smallList != rhs.end())
		{
			// This will be used for placing the value into the list
			insertPlace = find_gt(begin(), end(), *smallList);
			// This iterator will be used to check the value below insertPlace
			insertPlaceNext = find_gt(begin(), end(), *smallList);
			--insertPlaceNext;

			// Checking if the value can be inserted (there are no dublicates) and inserting it
			if (!(*insertPlace == *smallList) && !(*insertPlaceNext == *smallList))
			{
				insert(insertPlace, (*smallList));
			}

			// Adding to small list iterator
			++smallList;
		}

	}

private:
	int   theSize;
	Node* head;
	Node* tail;

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};

#endif