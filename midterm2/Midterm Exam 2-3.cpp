// Polynomial test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "Polynomial - Student ID - Mid 2.h"

template< typename T >
void input( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] );

const int numTestCases = 9;

int main()
{
   Polynomial< Term > multiplicand[ numTestCases ];
   Polynomial< Term > multiplier[ numTestCases ];

   input( multiplicand, multiplier );

   for( int i = 0; i < numTestCases; i++ )
   {
      cout << multiplicand[ i ] << endl;
      cout << multiplier[ i ] << endl;
      cout << multiplicand[ i ] * multiplier[ i ] << endl << endl;
   }

   ofstream outFile( "Result.txt", ios::out );

   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i < numTestCases; i++ )
   {
      outFile << multiplicand[ i ] << endl;
      outFile << multiplier[ i ] << endl;
      outFile << multiplicand[ i ] * multiplier[ i ] << endl << endl;
   }

   outFile.close();

   system( "pause" );
}

template< typename T >
void input( Polynomial< T > multiplicand[], Polynomial< T > multiplier[] )
{
   ifstream inFile( "Test cases.txt", ios::in );

   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int k = 0; k < numTestCases; k++ )
   {
      int numTerms;
      inFile >> numTerms;
      Term *terms = new Term[ numTerms ];
      for( int i = 0; i < numTerms; i++ )
         inFile >> terms[ i ].coef >> terms[ i ].expon;
      for( int i = 0; i < numTerms; i++ )
         multiplicand[ k ].insert( terms[ i ] );

      delete[] terms;
      inFile >> numTerms;
      terms = new Term[ numTerms ];
      for( int i = 0; i < numTerms; i++ )
         inFile >> terms[ i ].coef >> terms[ i ].expon;
      for( int i = 0; i < numTerms; i++ )
         multiplier[ k ].insert( terms[ i ] );
   }

   inFile.close();
}