#pragma once
#include "ArithmeticExpression.h"
class Number : public ArithmeticExpression
{
private:
	double value;
public:
	Number(double value) : value(value) {}
	double Evaluate() const override;
	ArithmeticExpression* Clone() const override;
};
