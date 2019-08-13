#include <string.h>

///////////////////////////////////////////////////////////////////////////////////

// returns if a bit is set
template <typename t>
bool TestBit( t data, int position )
{
	t mask = 1 << position ;
	return ( data & mask ) ? true : false ;
}

///////////////////////////////////////////////////////////////////////////////////

template <typename t>
t BitSet(t data, int position)
{
	t mask = 1 << position ;
	data |= mask ;
	return data ;
}

template< typename t >
t BitReset( t data, int position )
{
	t mask = 1 << position ;
	data &= ~mask ;
	return data ;
}

///////////////////////////////////////////////////////////////////////////////////

template <typename t>
t BitGetVal(t data, int position)
{
	t mask = 1 << position ;
	return ( data & mask ) ? 1 : 0 ;
}

///////////////////////////////////////////////////////////////////////////////////
