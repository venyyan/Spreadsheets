#pragma once
#include "ArithmeticExpression.h"
#include "Number.h"
#include "Expression.h"
#include "..\Utilities\MyString.h"
#include "..\Table\Table.h"
#include "..\Utilities\SharedPtr.hpp"
class ExpressionCalculator {
private:
	const Table* table;
	ArithmeticExpression* expr;

	ArithmeticExpression* ParseExpression(const MyString& str);
	int GetCell(size_t number, const MyString& str, int& rowDigitsCount) const;
public:
	ExpressionCalculator(const MyString& str, const Table* table);
	double Evaluate();
};
