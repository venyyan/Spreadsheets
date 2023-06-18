#include "Expression.h"
#include "..\Utilities\HelperFunctions.h"
#include <iostream>

Expression::Expression(char op, ArithmeticExpression* left, ArithmeticExpression* right)
	: op(op), left(left), right(right) {}

double Expression::Evaluate() const  {
	double leftVal = left->Evaluate();
	double rightVal = right->Evaluate();

	if (op == '+') {
		return leftVal + rightVal;
	}
	else if (op == '-') {
		return leftVal - rightVal;
	}
	else if (op == '*') {
		return leftVal * rightVal;
	}
	else if (op == '/') {
		if (rightVal == 0)
			throw std::logic_error("Error");

		return leftVal / rightVal;
	}
	else if (op == '^') {
		return Pow(leftVal, rightVal);
	}
}

ArithmeticExpression* Expression::Clone() const {
	return new Expression(op, left->Clone(), right->Clone());
}

Expression::~Expression() {
	delete right;
	delete left;
};