
#include "stdafx.h"
#include "X_Range.h"



X_Range::X_Range(double upper, double lower): upper(upper),lower(lower)
{
	if (lower > upper)
		exit(0);
}


X_Range::~X_Range()
{
}

double X_Range::getUpper() const
{
	return upper;
}

double X_Range::getLower() const
{
	return lower;
}
