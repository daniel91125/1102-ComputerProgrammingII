#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
using std::strlen;

// list standard header
#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
	using nodePtr = ListNode*;

	nodePtr next; // successor node, or first element if head
	nodePtr prev; // predecessor node, or last element if head
	ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
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

	ListVal() // initialize data
		: myHead(),
		mySize(0)
	{
	}

	nodePtr myHead; // pointer to head node
	size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
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

	using iterator = node*;
	using const_iterator = const node*;

	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	explicit list(size_type count) // construct list from count * Ty()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				//            insert( cend(), Ty() );
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

	void resize(size_type newSize)
	{
		if (myData.mySize < newSize) // pad to make larger
		{
			size_type difference = newSize - myData.mySize;
			for (size_type i = 0; i < difference; i++) // create newSize - myData.mySize elements
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

	bool empty() const
	{
		return myData.mySize == 0;
	}

	reference front()
	{
		return myData.myHead->next->myVal;
	}

	const_reference front() const
	{
		return myData.myHead->next->myVal;
	}

	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	const_reference back() const
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

	void clear() // erase all
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

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(list< Ty >& left, list< Ty >& right)
{
	if (left.size() != right.size())
		return false;

	typename list< Ty >::iterator it1 = left.begin();
	typename list< Ty >::iterator it2 = right.begin();

	for (; it1 != left.end(); it1 = it1->next, it2 = it2->next)
	{
		if (it1->myVal != it2->myVal)
			return false;
	}

	return true;
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=(list< Ty >& left, list< Ty >& right)
{
	return !(left == right);
}

#endif // LIST


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
	template< typename U >
	friend ostream& operator<<(ostream& output, HugeInteger< U > hugeInteger);
public:
	using value_type = typename T::value_type;
	using size_type = typename T::size_type;

	HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	// constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const T& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	bool operator==(HugeInteger& right); // less than or equal to

	bool operator<(HugeInteger& right);  // less than

	bool operator<=(HugeInteger& right); // less than or equal to

	HugeInteger square(value_type powerTwo); // the square of HugeInteger
	HugeInteger squareRoot(value_type powerTwo); // the square root of HugeInteger

	bool isZero();           // return true if and only if all digits are zero
private:
	T integer;
}; // end class HugeInteger

#endif

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const T& integerToCopy)
	: integer(integerToCopy)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{
	if (integer.size() < right.integer.size())
		return true;
	else if (integer.size() > right.integer.size())
		return false;

	typename T::iterator it = integer.end()->prev;
	typename T::iterator r_it = right.integer.end()->prev;

	for (; it != integer.begin()->prev; it = it->prev, r_it = r_it->prev)
	{
		if (it->myVal < r_it->myVal)
			return true;
		else if (it->myVal > r_it->myVal)
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

template< typename T >
HugeInteger< T > HugeInteger< T >::square(value_type powerTwo)
{
	HugeInteger zero;
	if (isZero())
		return zero;

	size_t squareSize = 2 * integer.size();
	HugeInteger square(squareSize);

	typename T::iterator it = integer.begin();
	typename T::iterator t_it = integer.begin();
	typename T::iterator s_it = square.integer.begin();

	for (int j = 0; it != integer.end(); it = it->next, ++j)
	{
		int k = 0;
		for (t_it = integer.begin(), s_it = square.integer.begin(); t_it != integer.end(); t_it = t_it->next, s_it = s_it->next)
		{
			size_t tmp = (it->myVal) * (t_it->myVal);
			while (k != j)
			{
				s_it = s_it->next;
				++k;
			}
			s_it->myVal += tmp;
		}
	}

	size_t tmp = 0;
	//typename T::value_type numDigits = sizeof(typename T::value_type) - 1;//判斷一格存幾位數
	//size_t val = 1;
	//for (int i = 0; i < numDigits; ++i)
	//	val *= 10;

	for (s_it = square.integer.begin(); s_it != square.integer.end(); s_it = s_it->next)
	{
		s_it->myVal += tmp;
		if ((s_it->myVal) > (powerTwo - 1))
		{
			tmp = (s_it->myVal) / powerTwo;
			(s_it->myVal) %= powerTwo;
		}
		else
			tmp = 0;
	}

	for (s_it = square.integer.end()->prev; s_it != square.integer.begin()->prev;)
	{
		if ((s_it->myVal) == 0)
		{
			s_it = s_it->prev;
			square.integer.pop_back();
		}
		else
			break;
	}

	return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot(value_type powerTwo)
{

	HugeInteger zero;
	if (isZero())
		return zero;

	size_type sqrtSize = (integer.size() + 1) / 2;
	HugeInteger sqrt(sqrtSize);

	//typename T::value_type numDigits = sizeof(typename T::value_type) - 1; //判斷一格存幾位數
	//size_t val = 1;
	//for (int i = 0; i < numDigits; ++i)
	//	val *= 10;

	typename T::iterator s_it = sqrt.integer.end()->prev;
	int check = sqrt.integer.size() - 1;

	while (check >= 0)
	{
		size_t low = 0;
		size_t high = powerTwo - 1;
		s_it->myVal = powerTwo - 1;

		while (low <= high) //binary search
		{
			size_t middle = (low + high) / 2;
			s_it->myVal = middle;

			HugeInteger buf(sqrt.square(powerTwo)); //square值不知道放什麼

			if (high == low)
			{
				if (*this < buf)
				{
					s_it->myVal = middle - 1;
					--check;
					break;
				}
				else
				{
					--check;
					break;
				}
			}

			if (*this == buf)
			{
				high = middle;
				--check;
			}
			if (*this < buf)
			{
				high = middle - 1;
				if (high < low)
				{
					s_it->myVal = middle - 1;
					--check;
				}
			}
			else
				low = middle + 1;
		}
		s_it = s_it->prev;
	}

	return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	typename T::iterator it = integer.begin();
	for (; it != integer.end(); it = it->next)
		if (it->myVal != 0)
			return false;

	return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	typename T::value_type numDigits = sizeof(typename T::value_type) - 1;
	typename T::iterator it = hugeInteger.integer.end()->prev;
	output << it->myVal;
	for (it = it->prev; it != hugeInteger.integer.begin()->prev; it = it->prev)
		output << setw(numDigits) << setfill('0') << it->myVal;

	return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
	char buf[1002];
	int numCases;
	cin >> numCases;
	for (int i = 1; i <= numCases; ++i)
	{
		cin >> buf;

		T digits[1001] = {};
		size_t last = strlen(buf) - 1;
		for (size_t i = 0; i <= last; ++i)
			digits[i] = static_cast<T>(buf[last - i]) - '0';

		list< T > integer;
		T powerTwo;
		size_t numDigits = sizeof(T) - 1;
		for (size_t i = 0; i <= last; i += numDigits)
		{
			powerTwo = 1;
			T bigDigit = 0;
			for (size_t j = i; j < i + numDigits; ++j, powerTwo *= 10)
				bigDigit += digits[j] * powerTwo;

			integer.push_back(bigDigit);
		}

		HugeInteger< list< T > > hugeInteger(integer);

		cout << hugeInteger.squareRoot(powerTwo) << endl;

		if (i < numCases)
			cout << endl;
	}
}

int main()
{
	int choice = 6;
	switch (choice)
	{
	case 1:
		solution< long int >();
		break;
	case 2:
		solution< unsigned long int >();
		break;
	case 3:
		solution< long long int >();
		break;
	case 4:
		solution< unsigned long long int >();
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}