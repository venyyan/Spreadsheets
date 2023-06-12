#pragma once
#include "ArithmeticExpression.h"
class Number : public ArithmeticExpression
{
private:
	double value;
public:
	Number(double value) : value(value) {}
	double Evaluate() const override { return value; }
	ArithmeticExpression* Clone() const override { return new Number(value); }
};
