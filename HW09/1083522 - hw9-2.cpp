#include <iostream>
#include <cmath>
using namespace std;

const int maxSize = 200;

template< typename BidIt >
class ReverseIterator
{
public:
	using value_type = typename BidIt::value_type;
	using difference_type = typename BidIt::difference_type;
	using pointer = typename BidIt::pointer;
	using reference = typename BidIt::reference;

	ReverseIterator() = default;

	ReverseIterator(BidIt right)
		: current(right)
	{
	}

	ReverseIterator(const ReverseIterator& right)
		: current(right.current)
	{
	}

	ReverseIterator& operator=(const ReverseIterator& right)
	{
		current = right.current;
		return *this;
	}

	BidIt base() const
	{
		return current;
	}

	reference operator*() const
	{
		BidIt tmp = current;
		return *--tmp;
	}

	ReverseIterator& operator++()
	{
		--current;
		return *this;
	}

protected:
	BidIt current{};
};

template< typename BidIt1, typename BidIt2 >
bool operator==(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return left.base() == right.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator!=(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return !(left == right);
}


template< typename MyVec >
class VectorConstIterator
{
public:
	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::const_pointer;
	using reference = const value_type&;
	using TPtr = typename MyVec::pointer;

	VectorConstIterator()
		: ptr()
	{
	}

	VectorConstIterator(TPtr parg)
		: ptr(parg)
	{
	}

	reference operator*() const
	{
		return *ptr;
	}

	VectorConstIterator& operator++()
	{
		++ptr;
		return *this;
	}

	VectorConstIterator& operator--()
	{
		--ptr;
		return *this;
	}

	bool operator==(const VectorConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VectorConstIterator& right) const
	{
		return !(*this == right);
	}

	TPtr ptr;
};


template< typename MyVec >
class VectorIterator : public VectorConstIterator< MyVec >
{
public:
	using MyBase = VectorConstIterator< MyVec >;

	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::pointer;
	using reference = value_type&;

	using MyBase::MyBase;

	reference operator*() const
	{
		return const_cast<reference>(MyBase::operator*());
	}

	VectorIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	VectorIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}
};


template< typename ValueType >
class VectorVal
{
public:
	using value_type = ValueType;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	VectorVal()
		: myFirst(),
		myLast(),
		myEnd()
	{
	}

	pointer myFirst; // pointer to beginning of array
	pointer myLast;  // pointer to current end of sequence
	pointer myEnd;   // pointer to end of array
};


template< typename Ty >
class vector
{
public:
	using value_type = Ty;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = Ty&;
	using const_reference = const Ty&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

private:
	using ScaryVal = VectorVal< Ty >;

public:
	using iterator = VectorIterator< ScaryVal >;
	using const_iterator = VectorConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	vector()
		: myData()
	{
	}

	vector(const size_type count)
		: myData()
	{
		resize(count);
	}

	vector(const vector& right)
		: myData()
	{
		*this = right;
	}

	~vector()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	void push_back(const Ty& val)
	{
		size_type originalSize = size();
		resize(originalSize + 1);
		myData.myFirst[originalSize] = val;
	}

	vector& operator=(const vector& right)
	{
		if (this != &right) // avoid self-assignment
		{
			size_type r_c = right.myData.myEnd - right.myData.myFirst;
			size_type r_s = right.myData.myLast - right.myData.myFirst;
			resize(r_s);
			for (size_type i = 0; i < r_s; i++)
			{
				myData.myFirst[i] = right.myData.myFirst[i];
			}
		}

		return *this; // enables x = y = z, for example
	}

	void resize(const size_type newSize)
	{
		if (newSize <= capacity())
		{
			myData.myLast = &myData.myFirst[newSize];
		}
		else
		{
			size_type t_capacity = capacity() * 1.5;
			if (t_capacity < newSize)
				t_capacity = newSize;
			pointer tmp = new value_type[t_capacity]();
			for (size_type i = 0; i < size(); i++)
			{
				tmp[i] = myData.myFirst[i];
			}
			if (myData.myFirst == nullptr)
				delete[] myData.myFirst;
			myData.myFirst = tmp;
			myData.myLast = tmp + newSize;
			myData.myEnd = tmp + t_capacity;
		}

	}

	void pop_back()
	{
		if (size() > 0)
			--myData.myLast;
	}

	void clear()
	{
		myData.myLast = myData.myFirst;
	}

	iterator begin()
	{
		return iterator(myData.myFirst);
	}

	iterator end()
	{
		return iterator(myData.myLast);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	size_type size() const
	{
		return static_cast<size_type>(myData.myLast - myData.myFirst);
	}

	size_type capacity() const
	{
		return static_cast<size_type>(myData.myEnd - myData.myFirst);
	}

	value_type& front()
	{
		return *myData.myFirst;
	}

	value_type& back()
	{
		return myData.myLast[-1];
	}

private:

	ScaryVal myData;
};

template< typename Ty >
bool operator==(vector< Ty >& left, vector< Ty >& right)
{
	if (left.size() != right.size())
		return false;
	if (left.capacity() != right.capacity())
		return false;

	typename vector< Ty >::iterator it1 = left.begin();
	typename vector< Ty >::iterator it2 = right.begin();
	for (; it1 != left.end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false; // vector contents are not equal

	return true; // vector contents are equal
}

template< typename Ty >
bool operator!=(vector< Ty >& left, vector< Ty >& right)
{
	return !(left == right);
}


template< typename MyList >
class ListConstIterator
{
public:
	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::const_pointer;
	using reference = const value_type&;

	ListConstIterator()
		: ptr()
	{
	}

	ListConstIterator(nodePtr pNode)
		: ptr(pNode)
	{
	}

	reference operator*() const
	{
		return ptr->myVal;
	}

	ListConstIterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	ListConstIterator& operator--()
	{
		ptr = ptr->prev;
		return *this;
	}

	bool operator==(const ListConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ListConstIterator& right) const
	{
		return !(*this == right);
	}

	nodePtr ptr;
};


template< typename MyList >
class ListIterator : public ListConstIterator< MyList >
{
public:
	using MyBase = ListConstIterator< MyList >;

	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::pointer;
	using reference = value_type&;

	using MyBase::MyBase;

	reference operator*() const
	{

		return const_cast<reference>(MyBase::operator*());
	}

	ListIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	ListIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}
};

template< typename ValueType >
struct ListNode
{
	using nodePtr = ListNode*;

	nodePtr next; // successor node, or first element if head
	nodePtr prev; // predecessor node, or last element if head
	ValueType myVal; // the stored value, unused if head
};


template< typename Ty >
class ListVal
{
public:
	using node = ListNode< Ty >;
	using nodePtr = node*;

	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	ListVal()
		: myHead(),
		mySize(0)
	{
	}

	nodePtr myHead; // pointer to head node
	size_type mySize; // number of elements
};


template< typename Ty >
class list
{
	using node = ListNode< Ty >;
	using nodePtr = node*;
	using ScaryVal = ListVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = ListIterator< ScaryVal >;
	using const_iterator = ListConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	list(size_type count)
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				push_back(Ty());
	}

	list(const list& right)
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
		*this = right;
	}

	~list()
	{
		clear();
		delete myData.myHead;
	}

	list& operator=(const list& right)
	{
		if (this != &right)
		{
			if (right.size() > size())
			{
				nodePtr current = myData.myHead->next;
				nodePtr r_current = right.myData.myHead->next;

				size_type tmp = right.size() - size();
				size_type i = 1;

				for (size_type i = 1; i <= right.size(); ++i)
				{
					if (i <= size())
					{
						current->myVal = r_current->myVal;
						current = current->next;
					}
					else
						push_back(r_current->myVal);

					r_current = r_current->next;
				}
			}
			else
			{
				nodePtr current = myData.myHead->next;
				nodePtr r_current = right.myData.myHead->next;

				size_type tmp = size() - right.size();

				while (r_current != right.myData.myHead)
				{
					current->myVal = r_current->myVal;
					current = current->next;
					r_current = r_current->next;
				}
				while (tmp)
				{
					pop_back();
					--tmp;
				}
			}
			myData.mySize = right.size();
		}
		return *this;
	}

	iterator begin()
	{
		return iterator(myData.myHead->next);
	}

	iterator end()
	{
		return iterator(myData.myHead);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void resize(size_type newSize)
	{
		if (myData.mySize < newSize)
		{
			size_type difference = newSize - myData.mySize;
			for (size_type i = 0; i < difference; i++)
				push_back(Ty());
		}
		else
		{
			while (newSize < myData.mySize)
				pop_back();
		}
	}

	size_type size() const
	{
		return myData.mySize;
	}

	reference front()
	{
		return myData.myHead->next->myVal;
	}

	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	void push_back(const Ty& val)
	{
		nodePtr tmp = new node;
		tmp->myVal = val;
		tmp->next = myData.myHead->prev->next;
		tmp->prev = myData.myHead->prev;
		myData.myHead->prev->next = tmp;
		myData.myHead->prev = tmp;
		myData.mySize++;
	}

	void pop_back()
	{
		if (myData.mySize > 0)
		{
			nodePtr tmp = myData.myHead->prev;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			myData.mySize--;
		}
	}

	void clear()
	{
		if (myData.mySize != 0) // the list is not empty
		{
			nodePtr tmp = myData.myHead->next;
			while (tmp != myData.myHead)
			{
				nodePtr tmp1 = tmp;
				tmp = tmp->next;
				delete tmp1;
			}
		}
	}

private:
	ScaryVal myData;
};

template< typename Ty >
bool operator==(list< Ty >& left, list< Ty >& right)
{
	if (left.size() != right.size())
		return false;

	typename list< Ty >::iterator it1 = left.begin();
	typename list< Ty >::iterator it2 = right.begin();

	for (; it1 != left.end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
			return false;
	}

	return true;
}

template< typename Ty >
bool operator!=(list< Ty >& left, list< Ty >& right)
{
	return !(left == right);
}


template< typename MyDeque >
class DequeConstIterator
{
private:
	using size_type = typename MyDeque::size_type;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::const_pointer;
	using reference = const value_type&;

	DequeConstIterator()
		: myOff(0),
		myCont(nullptr)
	{
	}

	DequeConstIterator(size_type off, const MyDeque* pDeque)
		: myOff(off),
		myCont(pDeque)
	{
	}

	DequeConstIterator(const DequeConstIterator& right)
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator()
	{
	}

	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this)
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this;
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	DequeConstIterator& operator++()
	{
		++myOff;
		return *this;
	}

	DequeConstIterator& operator--()
	{
		--myOff;
		return *this;
	}

	DequeConstIterator& operator+=(const difference_type off)
	{
		myOff += off;
		return *this;
	}

	DequeConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	bool operator==(const DequeConstIterator& right) const
	{
		return this->myCont == right.myCont && this->myOff == right.myOff;
	}

	bool operator!=(const DequeConstIterator& right) const
	{
		return !(*this == right);
	}

	const MyDeque* myCont; // keep a pointer to deque
	size_type myOff;       // offset of element in deque
};


template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	DequeIterator()
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque)
	{
	}

	reference operator*() const
	{
		return const_cast<reference>(MyBase::operator*());
	}

	DequeIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}

	DequeIterator& operator-=(const difference_type off)
	{
		MyBase::operator-=(off);
		return *this;
	}

	DequeIterator operator-(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp -= off;
	}
};

template< typename Ty >
class DequeVal
{
public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using MapPtr = Ty**;

	DequeVal()
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	size_type getBlock(size_type off) const
	{
		return off % (4 * mapSize) / 4;
		//      return ( off / 4 ) & ( mapSize - 1 );
	}

	MapPtr map;        // pointer to array of pointers to blocks
	size_type mapSize; // size of map array, zero or 2^N
	size_type myOff;   // offset of initial element
	size_type mySize;  // current length of sequence
};


template< typename Ty >
class deque
{
private:
	using MapPtr = Ty**;
	using ScaryVal = DequeVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = DequeIterator< ScaryVal >;
	using const_iterator = DequeConstIterator< ScaryVal >;

	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	deque()
		: myData()
	{
	}

	deque(size_type count)
		: myData()
	{
		resize(count);
	}

	deque(const deque& right)
		: myData()
	{
		if (right.myData.mySize != 0)
		{
			if (right.myData.mySize > 4 * (right.myData.mapSize - 1)) //擴增
			{
				size_type val = (right.myData.mapSize) * 2;
				MapPtr tmp = new value_type * [val]();

				for (int i = 0; i < val; ++i)
					tmp[i] = nullptr;

				size_type c = 0;
				for (size_type i = right.myData.myOff; i < right.myData.myOff + right.myData.mySize; i += 4)
				{
					++c;
				}

				for (size_type i = 0; i <= c; ++i)
				{
					pointer pt = new value_type[4]();
					tmp[i] = pt;
				}

				size_type count = 0;
				size_type row, col, row1, col1;
				for (size_type i = right.myData.myOff; i < right.myData.myOff + right.myData.mySize; ++i, ++count)
				{
					row = (count / 4) % val;
					col = count % 4;
					row1 = (i / 4) % right.myData.mapSize;
					col1 = i % 4;
					tmp[row][col] = right.myData.map[row1][col1];
				}

				if (myData.map != nullptr)
				{
					for (size_t i = 0; i < myData.mapSize; ++i)
						if (myData.map[i] != nullptr)
							delete[] myData.map[i];
					delete[] myData.map;
				}

				myData.map = tmp;
				myData.mapSize = val;
				myData.myOff = 0;
				myData.mySize = right.myData.mySize;
			}
			else //不擴增
			{
				size_type val = 0;
				if ((right.myData.myOff > 4 * right.myData.mapSize) && right.myData.mySize == 1)
					val = 8;
				else
					val = right.myData.mapSize;

				MapPtr tmp = new value_type * [val]();
				for (int i = 0; i < val; ++i) //讓map指向nullptr
					tmp[i] = nullptr;

				size_type count_row = 0;
				for (size_type i = right.myData.myOff; i < right.myData.myOff + right.myData.mySize; i += 4)
				{
					pointer pt = new value_type[4]();
					tmp[count_row] = pt;
					++count_row;
				}

				size_type count = 0;
				size_type row, col, row1, col1;
				for (size_type i = right.myData.myOff; i < right.myData.myOff + right.myData.mySize; ++i, ++count)
				{
					row = (count / 4) % val;
					col = count % 4;
					row1 = (i / 4) % right.myData.mapSize;
					col1 = i % 4;
					tmp[row][col] = right.myData.map[row1][col1];
				}

				if (myData.map != nullptr)
				{
					for (size_t i = 0; i < myData.mapSize; ++i)
						if (myData.map[i] != nullptr)
							delete[] myData.map[i];
					delete[] myData.map;
				}

				myData.map = tmp;
				myData.mapSize = val;
				myData.myOff = 0;
				myData.mySize = right.myData.mySize;
			}
		}
		else
		{
			myData.mySize = 0;
			myData.myOff = 0;
			myData.map = MapPtr();
		}
	}

	~deque()
	{
		clear();
	}

	deque& operator=(const deque& right)
	{
		if (&right != this) // avoid self-assignment
		{
			resize(right.myData.mySize);
			size_type row, col, row1, col1;
			size_type i = myData.myOff;
			for (size_type j = right.myData.myOff; j < right.myData.myOff + right.myData.mySize; ++j, ++i)
			{
				row = (i / 4) % myData.mapSize;
				col = i % 4;
				row1 = (j / 4) % right.myData.mapSize;
				col1 = j % 4;
				myData.map[row][col] = right.myData.map[row1][col1];
			}
		}

		return *this; // enables right = y = z, for example
	}

	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void resize(size_type newSize)
	{
		while (myData.mySize < newSize)
			push_back(value_type());

		while (newSize < myData.mySize)
			pop_back();
	}

	size_type size() const
	{
		return myData.mySize;
	}

	reference front()
	{
		return *begin();
	}

	reference back()
	{
		return *(end() - 1);
	}

	void push_back(const value_type& val)
	{
		if (myData.mySize == 0)
		{
			if (myData.mapSize == 0)
				myData.mapSize = 8;
			MapPtr tmp = new value_type * [myData.mapSize]();
			for (int i = 0; i < 8; ++i)
				tmp[i] = nullptr;
			size_type row = (myData.myOff / 4) % myData.mapSize;
			size_type col = myData.myOff % 4;
			pointer pt = new value_type[4]();
			pt[col] = val;
			tmp[row] = pt;

			if (myData.map != nullptr)
			{
				for (size_t i = 0; i < myData.mapSize; ++i)
					if (myData.map[i] != nullptr)
						delete[] myData.map[i];
				delete[] myData.map;
			}

			myData.map = tmp;
			myData.mySize++;
		}
		else
		{
			size_type newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
			if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
			{
				doubleMapSize();
				newBack = myData.myOff + myData.mySize;
				size_type row = (newBack / 4) % myData.mapSize;
				size_type col = newBack % 4;
				if (myData.map[row] != nullptr)
					myData.map[row][col] = val;
				else
				{
					pointer pt = new value_type[4]();
					pt[col] = val;
					myData.map[row] = pt;
				}
				myData.mySize++;
			}
			else
			{
				size_type tmp = myData.mySize + myData.myOff; //找出下一個位置
				size_type row = (tmp / 4) % myData.mapSize;
				size_type col = tmp % 4;
				if (myData.map[row] != nullptr)
					myData.map[row][col] = val;
				else
				{
					pointer pt = new value_type[4]();
					pt[col] = val;
					myData.map[row] = pt;
				}
				myData.mySize++;
				if (myData.myOff >= 4 * myData.mapSize)
					myData.myOff %= 4 * myData.mapSize;
			}
		}
	}

	void pop_back()
	{
		size_type back = (myData.myOff + myData.mySize - 1) % (4 * myData.mapSize);
		if (back % 4 == 0)
		{
			size_type front = myData.myOff % (4 * myData.mapSize);
			if (front > back && front <= back + 3)
			{
				delete[] myData.map[back / 4];
				myData.map[back / 4] = nullptr;
			}
		}

		--myData.mySize;
		if (myData.mySize == 0)
			myData.myOff = 0;
	}

	void clear()
	{
		if (myData.mapSize > 0)
		{
			for (size_type i = 0; i < myData.mapSize; i++)
				if (myData.map[i] != nullptr)
					delete[] myData.map[i];
			delete[] myData.map;

			myData.mapSize = 0;
			myData.mySize = 0;
			myData.myOff = 0;
			myData.map = MapPtr();
		}
	}

private:

	size_type getBlock(size_type off) const
	{
		return myData.getBlock(off);
		//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
	}

	void doubleMapSize()
	{
		size_type val = myData.mapSize * 2;
		MapPtr tmp = new value_type * [val]();
		for (int i = 0; i < val; ++i)
			tmp[i] = nullptr;

		for (size_type i = myData.myOff; i < myData.myOff + myData.mySize; i += 4) //先指向新的一個陣列
		{
			size_type row = (i / 4) % val;
			pointer pt = new value_type[4]();
			tmp[row] = pt;
		}

		//size_type test = 0;
		for (size_type i = myData.myOff; i < myData.myOff + myData.mySize; ++i) //再將東西放入
		{
			//++test;
			size_type row = (i / 4) % val;
			size_type col = i % 4;


			size_type row1 = (i / 4) % myData.mapSize;
			size_type col1 = i % 4;

			tmp[row][col] = myData.map[row1][col1];
		}

		for (size_type i = 0; i < myData.mapSize; ++i)
			delete[] myData.map[i];
		delete[] myData.map;

		myData.mapSize = val;
		myData.map = tmp;
	}

	ScaryVal myData;
};

template< typename Ty >
bool operator==(deque< Ty >& left, deque< Ty >& right)
{
	if (left.size() != right.size())
		return false;
	typename deque< Ty >::iterator l_it = left.begin();
	typename deque< Ty >::iterator r_it = right.begin();

	for (; l_it != left.end(); ++l_it, ++r_it)
	{
		if (*l_it != *r_it)
			return false;
	}
	return true;

}


template< typename T >
class HugeInteger
{
	template< typename U >
	friend ostream& operator<<(ostream& output, HugeInteger< U >& hugeInteger);
public:
	using value_type = typename T::value_type;
	using size_type = typename T::size_type;

	HugeInteger(size_type n = 0);
	HugeInteger(const HugeInteger& integerToCopy);
	~HugeInteger();
	const HugeInteger& operator=(const HugeInteger& right);
	bool operator==(HugeInteger& right);
	bool operator<(HugeInteger& right);
	bool operator<=(HugeInteger& right);
	void operator-=(HugeInteger& op2);
	void operator*=(HugeInteger& op2);
	HugeInteger operator/(HugeInteger& op2);
	HugeInteger operator%(HugeInteger& op2);
	HugeInteger& operator--();
	void convert(const value_type& number);
	void power(HugeInteger& base, const value_type& expon);
	size_type size();
	bool isZero();
	bool leadingZero();
private:
	T integer;
	void divideByTen();
	void helpDecrement();
};


template< typename T >
HugeInteger< T >::HugeInteger(size_type n)
	: integer((n == 0) ? 1 : n)
{
}

template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this)
		integer = right.integer;

	return *this;
}

template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
}

template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{
	if (integer.size() > right.integer.size())
		return false;
	else if (integer.size() < right.integer.size())
		return true;

	typename T::reverse_iterator it = integer.rbegin();
	typename T::reverse_iterator r_it = right.integer.rbegin();

	for (; it != integer.rend(); ++it, ++r_it)
	{
		if (*it < *r_it)
			return true;
		else if (*it > *r_it)
			return false;
	}

	return false;
} // end function operator<

template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

template< typename T >
void HugeInteger< T >::operator-=(HugeInteger& op2)
{
	HugeInteger zero;

	if (*this == op2)
	{
		*this = zero;
		return;
	}

	HugeInteger difference(*this);

	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = op2.integer.begin();
	typename T::iterator it3 = difference.integer.begin();

	int t = difference.integer.size() - 1;

	for (int j = 0; it3 != difference.integer.end() && j != t; ++it3, ++j)
	{
		*it3 += 10;
		if (it3 != difference.integer.begin())
			(*it3)--;
	}

	(*it3)--;

	for (it3 = difference.integer.begin(); it2 != op2.integer.end(); ++it3, ++it2)
		*it3 -= *it2;


	int j = 0;
	for (it3 = difference.integer.begin(); it3 != difference.integer.end() && j != t; ++it3, ++j)
		if (*it3 > 9)
		{
			*it3 -= 10;
			++it3;
			*it3 += 1;
			--it3;
		}

	typename T::reverse_iterator it4 = difference.integer.rbegin();

	int i = difference.integer.size() - 1;
	for (int j = 0; it4 != difference.integer.rend() && j != i; it4 = difference.integer.rbegin(),++j)
	{
		if (*it4 != 0)
			break;
		else if (*it4 == 0)
			difference.integer.pop_back();
	}

	if (difference.leadingZero())
		cout << "difference has a leading zero!\n";

	*this = difference;
}

template< typename T >
void HugeInteger< T >::operator*=(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
	{
		*this = zero;
		return;
	}

	HugeInteger product(integer.size() + op2.integer.size());

	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = op2.integer.begin();
	typename T::iterator it3 = product.integer.begin();

	for (int j = 0; it2 != op2.integer.end(); ++it2, ++j)
	{
		int k = 0;
		for (it1 = integer.begin(), it3 = product.integer.begin(); it1 != integer.end(); ++it1, ++it3)
		{
			size_t tmp = *it2 * *it1;
			while (k != j)
			{
				++it3;
				++k;
			}
			*it3 += tmp;
			if (*it3 > 9)
			{
				size_t t = *it3 / 10;
				*it3 %= 10;
				++it3;
				*it3 += t;
				--it3;
			}
		}
	}

	typename T::reverse_iterator it4 = product.integer.rbegin();

	for (; it4 != product.integer.rend(); it4 = product.integer.rbegin())
	{
		if (*it4 != 0)
			break;
		else if (*it4 == 0)
		{
			++it4;
			product.integer.pop_back();
		}
	}

	if (product.leadingZero())
		cout << "product has a leading zero!\n";

	*this = product;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger<T> buffer(integer.size());
	HugeInteger<T> remainder(*this);

	typename T::reverse_iterator it1 = buffer.integer.rbegin();
	typename T::reverse_iterator it2 = op2.integer.rbegin();
	typename T::reverse_iterator it4 = remainder.integer.rbegin();

	unsigned int n = integer.size() - op2.integer.size();
	if (n != 0)
	{
		for (it2 = op2.integer.rbegin(), it1 = buffer.integer.rbegin(); it2 != op2.integer.rend(); ++it2, ++it1)
		{
			*it1 = *it2;
		}
	}
	unsigned int quotientsize = integer.size() - op2.integer.size();

	if (*this < buffer)
		buffer.divideByTen();
	else
		quotientsize++;

	HugeInteger<T> quotient(quotientsize);

	typename T::reverse_iterator it3 = quotient.integer.rbegin();

	for (; it3 != quotient.integer.rend(); ++it3)
	{
		while (buffer <= remainder)
		{
			remainder -= buffer;
			*it3 += 1;
			if (remainder.isZero())
				return quotient;
		}
		buffer.divideByTen();
	}

	return quotient;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger remainder = *this;

	HugeInteger quotient = (*this) / op2;

	quotient *= op2;

	remainder -= quotient;

	return remainder;
}

template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement();
	return *this;
}

template< typename T >
void HugeInteger< T >::convert(const value_type& number)
{
	size_type numDigits = 0;
	typename T::iterator it = integer.begin();
	for (value_type i = number; i > 0; i /= 10, ++it, ++numDigits)
		*it = i % 10;
	integer.resize(numDigits);
}

template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;
	integer.pop_back();
}

template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; *it == 0; ++it)
		*it = 9;

	--(*it);

	if (leadingZero())
		integer.pop_back();
}

template< typename T >
void HugeInteger< T >::power(HugeInteger& base, const value_type& expon)
{
	*integer.begin() = 1;
	for (value_type i = 0; i < expon; ++i)
	{
		*this *= base;
		if (integer.size() > maxSize - base.integer.size())
			break;
	}
}

template< typename T >
typename HugeInteger< T >::size_type HugeInteger< T >::size()
{
	return integer.size();
}

template< typename T >
bool HugeInteger< T >::isZero()
{
	return (integer.size() == 1 && integer.front() == 0);
}

template< typename T >
bool HugeInteger< T >::leadingZero()
{
	return (integer.size() > 1 && integer.back() == 0);
}

template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T >& hugeInteger)
{
	typename T::reverse_iterator it = hugeInteger.integer.rbegin();
	for (; it != hugeInteger.integer.rend(); ++it)
		if (*it < 10)
			output << *it;

	return output;
}

template< typename T1, typename T2 >
void solution2()
{
	T2 t, a, b;
	while (cin >> t >> a >> b)
	{
		cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

		if (t == 1)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a == b)
			cout << "1\n";
		else if (a < b)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a % b != 0)
			cout << "is not an integer with less than 100 digits.\n";
		else if ((a - b) * static_cast<T2>(log10(t)) > 95)
			cout << "is not an integer with less than 100 digits.\n";
		else
		{
			HugeInteger< T1 > base(10);
			base.convert(t); // put all digits of t into base

			HugeInteger< T1 > dividend(1);
			dividend.power(base, a); // dividend = pow( t, a )

			if (dividend.size() > maxSize - base.size())
				cout << "is not an integer with less than 100 digits.\n";
			else
			{
				HugeInteger< T1 > divisor(1);
				divisor.power(base, b); // divisor = pow( t, b )

				if (divisor.size() > maxSize - base.size())
					cout << "is not an integer with less than 100 digits.\n";
				else
				{
					--dividend; // pow( t, a ) - 1
					--divisor;  // pow( t, b ) - 1

					HugeInteger< T1 > quotient = dividend / divisor;
					HugeInteger< T1 > remainder = dividend % divisor;

					if (quotient.leadingZero())
						cout << "quotient has a leading zero!\n";

					if (remainder.leadingZero())
						cout << "remainder has a leading zero!\n";

					// quotient is an integer with less than 100 digits
					if (quotient.size() < 100 && remainder.isZero())
						cout << quotient << endl;
					else
						cout << "is not an integer with less than 100 digits.\n";
				}
			}
		}
	}
}

template< typename T >
void solution1()
{
	T choice = 3;
	switch (choice)
	{
	case 1:
		solution2< vector< T >, T >();
		break;
	case 2:
		solution2< list< T >, T >();
		break;
	case 3:
		solution2< deque< T >, T >();
		break;
	default:
		cout << "Program should never get here!";
	}
}

int main()
{
	int choice = 1;
	switch (choice)
	{
	case 1:
		solution1< int >();
		break;
	case 2:
		solution1< unsigned int >();
		break;
	case 3:
		solution1< long int >();
		break;
	case 4:
		solution1< unsigned long int >();
		break;
	case 5:
		solution1< long long int >();
		break;
	case 6:
		solution1< unsigned long long int >();
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}