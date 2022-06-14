#include <iostream>
using std::cout;
using std::exit;

#include <algorithm>
using std::max;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   //mySize = count;
   //myRes = ( mySize / 16 ) * 16 + 15;
   resize(count);
   for (size_type i = 0; i < size(); i++)
   {
       myPtr()[i] = ptr[i];
   }

}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   //mySize = count;
   //if( count > 15 )
   //{
   //   myRes = ( mySize / 16 ) * 16 + 15;


   //}
    resize(count, ch);
}

string::string(const string& right)
    : bx(),
    mySize(0),
    myRes(15)
{
    *this = right;
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

//string& string::assign( const string &right )
string& string::operator=( const string &right )
{
    if (this != &right)
    {
        mySize = right.size();
        resize(mySize);
        for (size_type i = 0; i < size(); i++)
        {
            myPtr()[i] = right.myPtr()[i];
        }
        myPtr()[mySize] = '\0';
    }

    return *this;
}

bool string::operator==( const string &right )
{
    if (capacity() != capacity())
        return false;

    if (size() != right.size())
        return false;

    for (size_type i = 0; i < right.size(); i++)
    {
        if (myPtr()[i] != right.myPtr()[i])
            return false;
    }
    return true;
}

string& string::erase( const size_type off, size_type count )
{
    if (off < mySize)
    {
        if (count > size() - off)
            count = size() - off;

        for (size_type i = off; count + i < size(); i++)
        {
            myPtr()[i] = myPtr()[count + i];
        }
        mySize = size() - count;
        resize(mySize);
    }

    return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

//string::iterator string::end()
//{
//   return myPtr() + static_cast< difference_type >( mySize );
//}
//
//string::const_iterator string::end() const
//{
//   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
//}

// Returns a reference to the character at position pos in the string.
string::reference string::operator[]( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

// Returns a reference to the character at position pos in the string.
string::const_reference string::operator[]( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
    if (mySize > 0)
    {
        --mySize;
        myPtr()[mySize] = value_type();
    }
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch )
{
   // determine new length, padding with ch elements as needed
    if (newSize <= myRes)
    {
        for (size_type i = mySize; i < newSize; i++)
        {
            myPtr()[i] = ch;
        }
        mySize = newSize;
        myPtr()[mySize] = '\0';
    }
    else
    {
        size_type t_size = newSize | 15;
        size_type t_my = myRes * 1.5;
        size_type t_Res = 0;
        if (t_size > t_my)
            t_Res = t_size;
        else
            t_Res = t_my;

        pointer tmp = new value_type[t_Res + 1]();
        for (size_type i = 0; i < newSize; i++)
        {
            if (i < mySize)
                tmp[i] = myPtr()[i];
            else
                tmp[i] = ch;
        }

        mySize = newSize;
        if (myRes > 15)
            delete[] bx.ptr;
        myRes = t_Res;
        bx.ptr = tmp;
        myPtr()[mySize] = '\0';
    }
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}