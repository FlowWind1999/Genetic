#pragma once
class X_Range
{
private:
	double upper;
	double lower;
public:
	X_Range(double upper,double lower);
	~X_Range();
	double getUpper() const;
	double getLower() const;
};

