#include <iostream>
using std::cout;
using std::endl;

#include "Polynomial.h" // include definition of class Polynomial

Polynomial::Polynomial( size_t n )
   : polynomial( n )
{
}

Polynomial::Polynomial( size_t n, int coefficient[], int exponent[] )
   : polynomial( n )
{
   for( size_t i = 0; i < n; i++ )
   {
      polynomial.at( i ).coef = coefficient[ i ];
      polynomial.at( i ).expon = exponent[ i ];
   }
}

Polynomial::Polynomial( const Polynomial &right )
   : polynomial( right.polynomial )
{
}

Polynomial::~Polynomial()
{
}

const Polynomial Polynomial::assign( const Polynomial &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial.assign( right.polynomial );

   return *this; // enables x = y = z, for example
}

bool Polynomial::equal( const Polynomial &right )
{
   if( polynomial.size() != right.polynomial.size() )
      return false;

   for( size_t i = 0; i < polynomial.size(); i++ )
      if( polynomial.at( i ).coef != right.polynomial.at( i ).coef ||
          polynomial.at( i ).expon != right.polynomial.at( i ).expon )
         return false;

   return true;
}

void Polynomial::addition( const Polynomial &adder )
{
   //coef = 玒计, expon = 计
   Polynomial sum( polynomial.size() + adder.polynomial.size() );
   size_t i = 0; //砆计
   size_t j = 0; //计
   size_t k = 0; //㎝

   //よ猭
   while (i != polynomial.size() && j != adder.polynomial.size())
   {
       if (polynomial.at(i).expon < adder.polynomial.at(j).expon)
       {
           sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
           sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
           ++j;
           ++k;
       }
       else if (polynomial.at(i).expon == adder.polynomial.at(j).expon)
       {
           size_t tmp = polynomial.at(i).coef + adder.polynomial.at(j).coef;
           if (tmp != 0)
           {
               sum.polynomial.at(k).coef = tmp;
               sum.polynomial.at(k).expon = polynomial.at(i).expon;
               ++k;
           }
           ++i;
           ++j;
       }
       else
       {
           sum.polynomial.at(k).coef = polynomial.at(i).coef;
           sum.polynomial.at(k).expon = polynomial.at(i).expon;
           ++k;
           ++i;
       }
   }

   for (i; i < polynomial.size(); i++)
   {
       sum.polynomial.at(k).coef = polynomial.at(i).coef;
       sum.polynomial.at(k).expon = polynomial.at(i).expon;
       ++k;
   }
   for (j; j < adder.polynomial.size(); j++)
   {
       sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
       sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
       ++k;
   }


   //よ猭
   //for (i; i < polynomial.size(); i++)
   //{
   //    for (j; j < adder.polynomial.size() && i < polynomial.size(); j++)
   //    {
   //        if (polynomial.at(i).expon < adder.polynomial.at(j).expon)
   //        {
   //            sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
   //            sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
   //            ++k;
   //        }
   //        else if (polynomial.at(i).expon == adder.polynomial.at(j).expon)
   //        {
   //            size_t tmp = polynomial.at(i).coef + adder.polynomial.at(j).coef;
   //            if (tmp != 0)
   //            {
   //                sum.polynomial.at(k).coef = tmp;
   //                sum.polynomial.at(k).expon = polynomial.at(i).expon;
   //                ++k;
   //                ++i;
   //            }
   //            else
   //                ++i;
   //        }
   //        else
   //        {
   //            sum.polynomial.at(k).coef = polynomial.at(i).coef;
   //            sum.polynomial.at(k).expon = polynomial.at(i).expon;
   //            ++k;
   //            ++i;
   //            --j;
   //        }
   //    }
   //    if (i == polynomial.size())
   //        break;
   //    else if (j == adder.polynomial.size())
   //    {
   //        sum.polynomial.at(k).coef = polynomial.at(i).coef;
   //        sum.polynomial.at(k).expon = polynomial.at(i).expon;
   //        ++k;
   //    }
   //}
   //for (j; j < adder.polynomial.size(); j++)
   //{
   //    sum.polynomial.at(k).coef = adder.polynomial.at(j).coef;
   //    sum.polynomial.at(k).expon = adder.polynomial.at(j).expon;
   //    k++;
   //}

   if( sum.polynomial.size() != k )
      sum.polynomial.resize( k );

   polynomial.assign( sum.polynomial );

   if( !zero() && leadingCoef() == 0 )
      cout << "addend has leading zeroes!\n";
}

void Polynomial::subtraction( const Polynomial &subtrahend )
{
   Polynomial buffer( subtrahend.minus() );

   addition( buffer ); // minuend = minuend + buffer = minuend - subtrahend

   if( !zero() && leadingCoef() == 0 )
      cout << "minuend has leading zeroes!\n";
}

Polynomial Polynomial::multiplication( const Polynomial &multiplier ) const
{
   Polynomial product; //
   Polynomial buffer( polynomial.size() ); //–兜挡狦

   for (size_t i = 0; i < multiplier.polynomial.size(); i++)
   {
       for (size_t j = 0; j < polynomial.size(); j++)
       {
           size_t tmp_coef = multiplier.polynomial.at(i).coef * polynomial.at(j).coef;
           size_t tmp_expon = multiplier.polynomial.at(i).expon + polynomial.at(j).expon;
           buffer.polynomial.at(j).coef = tmp_coef;
           buffer.polynomial.at(j).expon = tmp_expon;
       }

       product.addition(buffer);
   }

   if( !product.zero() && product.leadingCoef() == 0 )
      cout << "product has leading zeroes!\n";

   return product;
}

Polynomial Polynomial::division( const Polynomial &divisor )
{
   //coef = 玒计, expon = 计
   Polynomial quotient;//坝
   Polynomial remainder( *this ); //砆埃计
   Polynomial monomial( 1 ); 
   Polynomial buffer(divisor.polynomial.size());
   
   while (remainder.polynomial.front().expon >= divisor.polynomial.front().expon && remainder.polynomial.size() != 0)
   {
       signed int tmp_coef = remainder.polynomial.front().coef / divisor.polynomial.front().coef;
       signed int tmp_expon = remainder.polynomial.front().expon - divisor.polynomial.front().expon;
       monomial.polynomial.at(0).coef = tmp_coef;
       monomial.polynomial.at(0).expon = tmp_expon;
       for (size_t i = 0; i < divisor.polynomial.size(); i++)
       {
           buffer.polynomial.at(i).coef = divisor.polynomial.at(i).coef * tmp_coef;
           buffer.polynomial.at(i).expon = divisor.polynomial.at(i).expon + tmp_expon;
       }
       
       quotient.polynomial.push_back(monomial.polynomial.at(0));


       remainder.subtraction(buffer);
   }

   if( !quotient.zero() && quotient.leadingCoef() == 0 )
      cout << "quotient has leading zeroes!\n";


   return quotient;
}

Polynomial Polynomial::modulus( const Polynomial &divisor )
{
   //coef = 玒计, expon = 计
   Polynomial quotient;//坝
   Polynomial remainder( *this ); //砆埃计
   Polynomial monomial( 1 ); 
   Polynomial buffer(divisor.polynomial.size());
   
   while (remainder.polynomial.front().expon >= divisor.polynomial.front().expon && remainder.polynomial.size() != 0)
   {
       signed int tmp_coef = remainder.polynomial.front().coef / divisor.polynomial.front().coef;
       signed int tmp_expon = remainder.polynomial.front().expon - divisor.polynomial.front().expon;
       monomial.polynomial.at(0).coef = tmp_coef;
       monomial.polynomial.at(0).expon = tmp_expon;
       for (size_t i = 0; i < divisor.polynomial.size(); i++)
       {
           buffer.polynomial.at(i).coef = divisor.polynomial.at(i).coef * tmp_coef;
           buffer.polynomial.at(i).expon = divisor.polynomial.at(i).expon + tmp_expon;
       }
       
       quotient.polynomial.push_back(monomial.polynomial.at(0));


       remainder.subtraction(buffer);
   }

   if( !quotient.zero() && quotient.leadingCoef() == 0 )
      cout << "quotient has leading zeroes!\n";

   return remainder;
}

void Polynomial::output()
{
   // the current polynomial is zero polynomial
   if( zero() )
      cout << 0;
   else
   {
      if( leadingCoef() < 0 )
         cout << "-" << -leadingCoef();
      else if( leadingCoef() > 0 )
         cout << leadingCoef();

      if( degree() > 0 )
      {
         if( degree() == 1 )
            cout << "x";
         else
            cout << "x^" << degree();
      }

      for( size_t i = 1; i < polynomial.size(); i++ )
      {
         if( polynomial.at( i ).coef < 0 )
            cout << " - " << -polynomial.at( i ).coef;
         else if( polynomial.at( i ).coef > 0 )
            cout << " + " << polynomial.at( i ).coef;

         if( polynomial.at( i ).expon > 0 )
         {
            if( polynomial.at( i ).expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial.at( i ).expon;
         }
      }
   }

   cout << endl;
}

bool Polynomial::hasZeroTerm()
{
   if( !zero() )
      for( size_t i = 0; i < polynomial.size(); i++ )
         if( polynomial.at( i ).coef == 0 )
            return true;

   return false;
}

Polynomial Polynomial::minus() const
{
   Polynomial minus( polynomial.size() );
   for( size_t i = 0; i < minus.polynomial.size(); i++ )
   {
      minus.polynomial.at( i ).coef = -polynomial.at( i ).coef;
      minus.polynomial.at( i ).expon = polynomial.at( i ).expon;
   }

   return minus;
}

bool Polynomial::zero() const
{
   return polynomial.empty();
}

int Polynomial::degree() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().expon;
}

int Polynomial::leadingCoef() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().coef;
}