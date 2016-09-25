//$ nocpp

// 2-dimensional function test corpus.

#ifndef TESTOPT_INCLUDED
#define TESTOPT_INCLUDED

#include "bitefan.h"

#if !defined( sqr )
	#define sqr( x ) (( x ) * ( x ))
#endif // !defined( sqr )

#if !defined( M_PI )
	#define M_PI 3.14159265358979324
#endif // !defined( M_PI )

const int ParamCount = 2;
CBEORnd rnd;

/**
 * Optimization test class.
 */

class CTestOpt : public CBEOOptimizerFan< ParamCount >
{
public:
	int fn;
	double sign1;
	double sign2;

	virtual void getMinValues( double* const p ) const
	{
		if( fn == 15 )
		{
			p[ 0 ] = -15;
			p[ 1 ] = -3;
		}
		else
		{
			p[ 0 ] = -10 + rnd.getRndValue() * 6.0;
			p[ 1 ] = -10 + rnd.getRndValue() * 6.0;
		}
	}

	virtual void getMaxValues( double* const p ) const
	{
		if( fn == 15 )
		{
			p[ 0 ] = -5;
			p[ 1 ] = 3;
		}
		else
		{
			p[ 0 ] = 10 - rnd.getRndValue() * 6.0;
			p[ 1 ] = 10 - rnd.getRndValue() * 6.0;
		}
	}

	virtual double optcost( const double* const p ) const
	{
		const double x = p[ 0 ] * ( fn == 9 ? 1.0 : sign1 );
		const double y = p[ 1 ] * ( fn == 9 ? 1.0 : sign2 );
		const double xa = x * 100;
		const double ya = y * 100;

		if( fn == 1 ) return( sqr( x + 2 * y - 7 ) + sqr( 2 * x + y - 5 ));
		if( fn == 2 ) return( 0.26 * ( x * x + y * y ) - 0.48 * x * y );
		if( fn == 3 ) return( x * x + y * y );
		if( fn == 4 ) return( sqr( sin( 3 * M_PI * x )) + sqr( x - 1 ) * ( 1 + sqr( sin( 3 * M_PI * y ))) + sqr( y - 1 ) * ( 1 + sqr( sin( 2 * M_PI * y ))));
		if( fn == 5 ) return( 0.5 + ( sqr( sin( x * x - y * y )) - 0.5 ) / sqr( 1 + 0.001 * ( x * x + y * y )));
		if( fn == 6 ) return( -20 * exp( -0.2 * sqrt( 0.5 * ( x * x + y * y ))) - exp( 0.5 * ( cos( 2 * M_PI * x ) + cos( 2 * M_PI * y ))) + 2.71828182845904524 + 20 );
		if( fn == 7 ) return( 100 * sqr( y - x * x ) + sqr( x - 1 ));
		if( fn == 8 ) return( sqr( 1.5 - x + x * y ) + sqr( 2.25 - x + x * y * y ) + sqr( 2.625 - x + x * y * y * y ));
		if( fn == 9 ) return( -cos(x)*cos(y)*exp(-(sqr(x-M_PI)+sqr(y-M_PI))) + 1 );
		if( fn == 10 ) return( -0.0001 * pow( fabs(sin(x)*sin(y)*exp(fabs(100-sqrt(x*x+y*y)/M_PI)))+1, 0.1 ) + 2.06261 );
		if( fn == 11 ) return( 0.5+(sqr(cos(sin(fabs(x*x-y*y))))-0.5)/sqr(1+0.001*(x*x+y*y)) - 0.292579 );
		if( fn == 12 ) return( (1+sqr(x+y+1)*(19-14*x+3*x*x-14*y+6*x*y+3*y*y))*(30+sqr(2*x-3*y)*(18-32*x+12*x*x+48*y-36*x*y+27*y*y)) - 3 );
		if( fn == 13 ) return( -(ya+47)*sin(sqrt(fabs(xa/2+ya+47))) - xa*sin(sqrt(fabs(xa-(ya+47)))) + 959.6407 );
		if( fn == 14 ) return( -fabs(sin(x)*cos(y)*exp(fabs(1.0-sqrt(x*x+y*y)/M_PI))) + 19.2085 );
		if( fn == 15 ) return( 100 * sqrt( fabs( y - 0.01 * x * x )) + 0.01 * fabs( x + 10 ));
		return( 2 * x * x - 1.05 * sqr( sqr( x )) + sqr( sqr( sqr( x ))) / 6 + x * y + y * y );
	}
};

#endif // TESTOPT_INCLUDED
