#pragma once
class ArithmeticExpression
{
public:
	virtual double Evaluate() const = 0;
	virtual ArithmeticExpression* Clone() const = 0;
	virtual ~ArithmeticExpression() = default;
};