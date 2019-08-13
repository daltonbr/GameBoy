#pragma once
#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <vector>
#include <stdio.h>
#include <assert.h>


#include "LogMessages.h"

template< typename typeData >
bool TestBit( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	return ( inData & lMsk ) ? true : false ;
}

template< typename typeData >
typeData BitGet( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	return lMsk ;
}

template< typename typeData >
typeData BitGetVal( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	return ( inData & lMsk ) ? 1 : 0 ;
}

template< typename typeData >
typeData BitSet( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	inData |= lMsk ;
	return inData ;
}

template< typename typeData >
typeData BitReset( typeData inData, size_t inBitPosition )
{
	typeData lMsk = 1 << inBitPosition ;
	inData &= ~lMsk ;
	return inData ;
}


#endif
