#include "Number.h"

double Number::Evaluate() const {
	return value;
}

ArithmeticExpression* Number::Clone() const {
	return new Number(value); 
}