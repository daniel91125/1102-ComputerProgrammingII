// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector - 1083522 - Mid 1.h"

template< typename T >
void testVector();

template< typename T >
void testFillConstructor();

template< typename T >
void testCopyConstructor();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testInsertErase();

// Determines if two vectors are equal.
template< typename T >
bool equal( vector< T > &left, std::vector< T > &right );

const unsigned int number = 1000;

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   switch( 1 + rand() % 6 )
   {
   case 1:
      testVector< int >();
      break;
   case 2:
      testVector< unsigned int >();
      break;
   case 3:
      testVector< short int >();
      break;
   case 4:
      testVector< unsigned short int >();
      break;
   case 5:
      testVector< long long int >();
      break;
   case 6:
      testVector< unsigned long long int >();
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}

template< typename T >
void testVector()
{
   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testFillConstructor< T >();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testCopyConstructor< T >();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert1< T >();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert2< T >();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsertErase< T >();
   }
}

template< typename T >
void testFillConstructor()
{
   unsigned int numErrors = number;
   size_t length;
   for( unsigned int i = 0; i < number; i++ )
   {
      length = rand() % 200;
      vector< T > vector1( length );
      std::vector< T > vector2( length );

      if( equal( vector1, vector2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testCopyConstructor()
{
   unsigned int numErrors = number;
   size_t length;
   T value;
   for( unsigned int i = 0; i < number; i++ )
   {
      vector< T > vector1;
      std::vector< T > vector2;
      length = rand() % 200;
      for( size_t j = 0; j < length; j++ )
      {
         value = 1 + static_cast< T >( rand() % 99 );
         vector1.insert( vector1.end(), value );
         vector2.insert( vector2.end(), value );
      }

      vector< T > vector3( vector1 );
      std::vector< T > vector4( vector2 );

      if( equal( vector3, vector4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testInsert1()
{
   vector< T > vector1;
   std::vector< T > vector2;

   unsigned int numErrors = number;
   unsigned int position;
   T value;
   for( unsigned int i = 0; i < number; i++ )
   {
      position = rand() % ( vector1.size() + 1 );
      value = 1 + static_cast< T >( rand() % 99 );

      typename vector< T >::iterator it1;
      typename std::vector< T >::iterator it2;
      it1 = vector1.insert( vector1.begin() + position, value );
      it2 = vector2.insert( vector2.begin() + position, value );

      if( equal( vector1, vector2 ) && *it1 == *it2 )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testInsert2()
{
   vector< T > v;

   unsigned int numErrors = number;
   unsigned int position;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      size_t oldSize = v.size();
      size_t oldCapacity = v.capacity();

      T *oldAddress = v.begin(); // oldAddress = v.myData.myFirst

      position = rand() % ( v.size() + 1 );
      value = 1 + rand() % 99;
      v.insert( v.begin() + position, value );

      T *newAddress = v.begin(); // newAddress = v.myData.myFirst

      if( oldSize == oldCapacity )
         numErrors--;
      else
         if( newAddress == oldAddress )
            numErrors--;
   }

   // newAddress == oldAddress if and only if
   // the array pointed by v.myData.myFirst before
   // the excution of v.insert( v.begin() + position, value ) is the same as
   // the array pointed by v.myData.myFirst after
   // the excution of v.insert( v.begin() + position, value )
   // i.e., there is no memory allocation during the excution of
   // v.insert( v.begin() + position, value )

   cout << "There are " << numErrors << " errors.\n";
}

template< typename T >
void testInsertErase()
{
   vector< T > vector1;
   std::vector< T > vector2;

   unsigned int numErrors = number; // number of errors
   unsigned int position;
   T value;
   for( unsigned int i = 0; i < number; i++ )
   {
      switch( rand() % 2 )
      {
      case 0:
         position = rand() % ( vector1.size() + 1 );
         value = 1 + static_cast< T >( rand() % 99 );
         vector1.insert( vector1.begin() + position, value );
         vector2.insert( vector2.begin() + position, value );
         break;
      case 1:
         if( !vector1.empty() )
         {
            position = rand() % vector1.size();
            vector1.erase( vector1.begin() + position );
            vector2.erase( vector2.begin() + position );
         }
         break;
      default:
         break;
      }

      if( equal( vector1, vector2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two vectors are equal.
template< typename T >
bool equal( vector< T > &left, std::vector< T > &right )
{
   if( left.capacity() != right.capacity() )
      return false;

   if( left.size() != right.size() )
      return false;

   for( size_t i = 0; i < right.size(); ++i )
      if( left[ i ] != right[ i ] )
         return false;

   return true;
}