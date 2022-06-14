#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "deque - 1083522 - Mid 2-1.h"

bool equal( std::deque< int > &deque1, deque< int > &deque2 );

int main()
{
   const size_t maxMapSize = 128;
   size_t numErrors = 0;

   std::deque< int > deque1;
   int ***map1 = reinterpret_cast< int *** > ( &deque1 ) + 1;
   size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
   size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
   size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

   deque< int > deque2;
   int ***map2 = reinterpret_cast< int *** > ( &deque2 );
   size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
   size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
   size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

   *myOff1 = 0;
   *myOff2 = 0;
   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      *mapSize1 = mapSize;
      *mapSize2 = mapSize;
      *map1 = new int*[ mapSize ]();
      *map2 = new int*[ mapSize ]();
      for( size_t mySize = 0; mySize <= 4 * mapSize; ++mySize )
      {
         *mySize1 = mySize;
         *mySize2 = mySize;
         if( mySize > 0 )
         {
            for( size_t block = 0; block <= ( mySize - 1 ) / 4; block++ )
            {
               ( *map1 )[ block ] = new int[ 4 ];
               ( *map2 )[ block ] = new int[ 4 ];
            }

            for( size_t i = 0; i < mySize; i++ )
            {
               ( *map1 )[ i / 4 ][ i % 4 ] = static_cast< int >( i );
               ( *map2 )[ i / 4 ][ i % 4 ] = static_cast< int >( i );
            }
         }

         std::deque< int > deque3( deque1 );
         deque< int > deque4( deque2 );


         if( !equal( deque3, deque4 ) )
            numErrors++;

         if( mySize > 0 && ( mapSize < maxMapSize || mySize < 4 * mapSize ) )
            for( size_t block = 0; block <= ( mySize - 1 ) / 4; block++ )
            {
               delete[] ( *map1 )[ block ];
               delete[] ( *map2 )[ block ];
            }
      }

      if( mapSize < maxMapSize )
      {
         delete[]( *map1 );
         delete[]( *map2 );
      }
   }

   cout << "There are " << numErrors << " errors\n\n";

   system( "pause" );
}

bool equal( std::deque< int > &deque1, deque< int > &deque2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &deque1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &deque1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 4 );

   int **map2 = *( reinterpret_cast< int *** > ( &deque2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

   if( mapSize1 != mapSize2 )
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

   if( myOff1 != myOff2 )
      return false;

   if( mySize1 != mySize2 )
      return false;

   size_t row, col;
   for( size_t i = 0; i < 4 * mapSize1; ++i )
   {
      row = ( i / 4 ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}