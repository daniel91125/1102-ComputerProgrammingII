#include <iostream>
#include <cmath>
using namespace std;

const int maxSize = 200;

template< typename BidIt >
class ReverseIterator // wrap iterator to run it backwards
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
		: current(right.current) // initialize with compatible base
	{
	}

	// assign from compatible base
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

	pointer operator->() const
	{
		BidIt tmp = current;
		--tmp;
		return tmp.operator->();
	}

	ReverseIterator& operator++()
	{
		--current;
		return *this;
	}

	ReverseIterator operator++(int)
	{
		ReverseIterator tmp = *this;
		--current;
		return tmp;
	}

	ReverseIterator& operator--()
	{
		++current;
		return *this;
	}

	ReverseIterator operator--(int)
	{
		ReverseIterator tmp = *this;
		++current;
		return tmp;
	}

	// increment by integer
	ReverseIterator& operator+=(const difference_type off)
	{
		current -= off;
		return *this;
	}

	// return this + integer
	ReverseIterator operator+(const difference_type off) const
	{
		return ReverseIterator(current - off);
	}

	// decrement by integer
	ReverseIterator& operator-=(const difference_type off)
	{
		current += off;
		return *this;
	}

	// return this - integer
	ReverseIterator operator-(const difference_type off) const
	{
		return ReverseIterator(current + off);
	}

	// subscript
	reference operator[](const difference_type off) const
	{
		return current[static_cast<difference_type>(-off - 1)];
	}

protected:
	BidIt current{}; // the wrapped iterator
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

template< typename BidIt1, typename BidIt2 >
bool operator<(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return right.base() < left.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator>(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return right < left;
}

template< typename BidIt1, typename BidIt2 >
bool operator<=(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return !(right < left);
}

template< typename BidIt1, typename BidIt2 >
bool operator>=(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return !(left < right);
}


// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
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

	DequeConstIterator(const DequeConstIterator& right) // copy constructor
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator() // destructor
	{
	}

	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this) // avoid self-assignment
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this; // enables x = y = z, for example
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	DequeConstIterator& operator++() // preincrement
	{
		++myOff;
		return *this;
	}

	DequeConstIterator& operator--() // predecrement
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


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	DequeIterator() // construct with null deque pointer
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque) // construct with offset off in *pDeque
	{
	}

	reference operator*() const // return designated object
	{
		return const_cast<reference>(MyBase::operator*());
	}

	pointer operator->() const // return pointer to class object
	{
		return const_cast<pointer>(MyBase::operator->());
		//      return &( operator*() );
	}

	DequeIterator& operator++() // preincrement
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator& operator--() // predecrement
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

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
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

	DequeVal() // initialize values
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	// determine block from offset
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


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
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

	// construct empty deque
	deque()
		: myData()
	{
	}

	// fill constructor
	// Constructs a container with "count" elements.
	// Each element is initialized as 0.
	deque(size_type count)
		: myData()
	{
		resize(count);
	}

	// construct by copying right
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

	// destroy the deque
	~deque()
	{
		clear();
	}

	// Assigns new contents to the container, replacing its current contents,
	// and modifying its size accordingly.
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
	} // end function operator=

	// return iterator for beginning of mutable sequence
	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	// return iterator for end of mutable sequence
	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for beginning of reversed mutable sequence
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	// return iterator for end of reversed mutable sequence
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

	// return length of sequence
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

	// insert element at end
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

	// erase element at end
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

	// determine block from offset
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

// test for deque equality
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
class HugeInteger : public deque< T >
{
private:
	using MyBase = deque< T >;

public:
	using value_type = typename MyBase::value_type;
	using size_type = typename MyBase::size_type;

	HugeInteger(size_type n = 0); // constructor; construct a zero HugeInteger with size n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger& operator=(const HugeInteger& right); // assignment operator

	bool operator==(HugeInteger& right); // less than or equal to

	bool operator<(HugeInteger& right);  // less than

	bool operator<=(HugeInteger& right); // less than or equal to

	// subtraction operator; HugeInteger -= HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	void operator-=(HugeInteger& op2);

	// multiplication operator; HugeInteger *= HugeInteger
	void operator*=(HugeInteger& op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger& op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger& op2);

	HugeInteger& operator--();     // prefix decrement operator

	void convert(const value_type& number); // convert an integer into a HugeInteger

	// compute base raised to the power of expon
	void power(HugeInteger& base, const value_type& expon);

	// return true if and only if there is only one digit and this digit is zero
	bool isZero();

	bool leadingZero(); // return true if and only if the leftmost digit is zero

private:
	void divideByTen();   // divides a HugeInteger by 10
	void helpDecrement(); // decrements a HugeInteger by 1

}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(size_type n)
	: deque< T >((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: deque< T >(integerToCopy)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		deque< T >::operator=(right);

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return ::operator==(*this, right);
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{
	if (this->size() < right.size())
		return true;
	else if (this->size() > right.size())
		return false;
	typename deque< T >::reverse_iterator it = this->rbegin();
	typename deque< T >::reverse_iterator r_it = right.rbegin();

	for (; it != this->rend(); ++it, ++r_it)
	{
		if (*it < *r_it)
			return true;
		else if (*it > *r_it)
			return false;
	}
	return false;

} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

// subtraction operator; HugeInteger - HugeInteger
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

	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it2 = op2.begin();
	typename deque< T >::iterator it3 = difference.begin();

	for (; it3 != difference.end() - 1; ++it3)
	{
		*it3 += 10;
		if (it3 != difference.begin())
			(*it3)--;
	}

	typename deque< T >::reverse_iterator it = difference.rbegin();

	it3 = difference.end() - 1;
	(*it3)--;

	for (it3 = difference.begin(); it2 != op2.end(); ++it3, ++it2)
	{
		*it3 -= *it2;
	}


	for (it3 = difference.begin(); it3 != difference.end() - 1; ++it3)
		if (*it3 > 9)
		{
			*it3 -= 10;
			++it3;
			*it3 += 1;
			--it3;
		}


	typename deque< T >::reverse_iterator it4 = difference.rbegin();

	for (; it4 != difference.rend(); ++it4)
	{
		if (*it4 != 0)
			break;
		else if (*it4 == 0)
			difference.pop_back();
	}

	if (difference.leadingZero())
		cout << "difference has a leading zero!\n";

	*this = difference;
} // end function operator-

// multiplication operator; HugeInteger * HugeInteger
template< typename T >
void HugeInteger< T >::operator*=(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
	{
		*this = zero;
		return;
	}

	HugeInteger product(this->size() + op2.size());

	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it2 = op2.begin();
	typename deque< T >::iterator it3 = product.begin();

	for (int j = 0; it2 != op2.end(); ++it2, ++j)
	{
		int k = 0;
		for (it1 = this->begin(),it3 = product.begin(); it1 != this->end(); ++it1, ++it3)
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


	typename deque< T >::reverse_iterator it4 = product.rbegin();

	for (; it4 != product.rend(); ++it4)
	{
		if (*it4 != 0)
			break;
		else if (*it4 == 0)
			product.pop_back();
	}

	if (product.leadingZero())
		cout << "product has a leading zero!\n";

	*this = product;
} // end function operator*

// division operator; HugeInteger / HugeInteger provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger<T> buffer(this->size());
	HugeInteger<T> remainder(*this);

	typename deque< T >::reverse_iterator it1 = buffer.rbegin();
	typename deque< T >::reverse_iterator it2 = op2.rbegin();
	typename deque< T >::reverse_iterator it4 = remainder.rbegin();

	unsigned int n = this->size() - op2.size();
	if (n != 0)
	{
		for (it2 = op2.rbegin(), it1 = buffer.rbegin(); it2 != op2.rend(); ++it2, ++it1)
		{
			*it1 = *it2;
		}
	}
	unsigned int quotientsize = this->size() - op2.size();

	if (*this < buffer)
		buffer.divideByTen();
	else
		quotientsize++;

	HugeInteger<T> quotient(quotientsize);

	typename deque< T >::reverse_iterator it3 = quotient.rbegin();

	for (; it3 != quotient.rend(); ++it3)
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
} // end function operator/

// modulus operator; HugeInteger % HugeInteger provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger remainder = *this;
	HugeInteger quotient = (*this) / op2;
	quotient *= op2;
	remainder -= quotient;
	return remainder;
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// convert an integer into a HugeInteger
template< typename T >
void HugeInteger< T >::convert(const value_type& number)
{
	size_type numDigits = 0;
	typename deque< T >::iterator it = this->begin();
	for (value_type i = number; i > 0; i /= 10, ++it, ++numDigits)
		*it = i % 10;
	this->resize(numDigits);
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it2 = it1;
	for (++it2; it2 != this->end(); ++it1, ++it2)
		*it1 = *it2;
	this->pop_back();
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename deque< T >::iterator it = this->begin();
	for (; *it == 0; ++it)
		*it = 9;

	--(*it);

	if (leadingZero())
		this->pop_back();
}

template< typename T >
void HugeInteger< T >::power(HugeInteger& base, const value_type& expon)
{
	*this->begin() = 1;
	for (value_type i = 0; i < expon; ++i)
	{
		*this *= base;
		if (this->size() > maxSize - base.size())
			break;
	}
}

// returns true if and only if the specified huge integer is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	return (this->size() == 1 && this->front() == 0);
}

template< typename T >
bool HugeInteger< T >::leadingZero()
{
	return (this->size() > 1 && this->back() == 0);
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T >& hugeInteger)
{
	typename deque< T >::reverse_iterator it = hugeInteger.rbegin();
	for (; it != hugeInteger.rend(); ++it)
		if (*it < 10)
			output << *it;

	return output; // enables cout << x << y;
}

template< typename T >
void solution()
{
	T t, a, b;
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
		else if ((a - b) * static_cast<T>(log10(t)) > 95)
			cout << "is not an integer with less than 100 digits.\n";
		else
		{
			HugeInteger< T > base(10);
			base.convert(t); // put all digits of t into base

			HugeInteger< T > dividend(1);
			dividend.power(base, a); // dividend = pow( t, a )

			if (dividend.size() > maxSize - base.size())
				cout << "is not an integer with less than 100 digits.\n";
			else
			{
				HugeInteger< T > divisor(1);
				divisor.power(base, b); // divisor = pow( t, b )

				if (divisor.size() > maxSize - base.size())
					cout << "is not an integer with less than 100 digits.\n";
				else
				{
					--dividend; // pow( t, a ) - 1
					--divisor;  // pow( t, b ) - 1

					HugeInteger< T > quotient = dividend / divisor;

					HugeInteger< T > remainder = dividend % divisor;

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

int main()
{
	int choice = 2;
	switch (choice)
	{
	case 1:
		solution< int >();
		break;
	case 2:
		solution< unsigned int >();
		break;
	case 3:
		solution< long int >();
		break;
	case 4:
		solution< unsigned long int >();
		break;
	case 5:
		solution< long long int >();
		break;
	case 6:
		solution< unsigned long long int >();
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}