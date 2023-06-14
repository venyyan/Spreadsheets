#pragma once
#include "ArithmeticExpression.h"

class Expression : public ArithmeticExpression
{
private:
	char op;
	ArithmeticExpression* left;
	ArithmeticExpression* right;

public:
	Expression(char op, ArithmeticExpression* left, ArithmeticExpression* right);

	double Evaluate() const override;
	ArithmeticExpression* Clone() const override;
	~Expression();
};

