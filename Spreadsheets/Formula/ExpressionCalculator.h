#pragma once
#include "ArithmeticExpression.h"
#include "Number.h"
#include "Expression.h"
#include "..\Utilities\MyString.h"
#include "..\Utilities\UniquePtr.hpp"
#include "..\Table\Table.h"
#include "..\Utilities\SharedPtr.hpp"
class ExpressionCalculator
{

private:
	//make it with unique
	const Table* table;
	ArithmeticExpression* expr;
	

	bool IsOperator(char op);
	ArithmeticExpression* ParseExpression(const MyString& str);

	int GetCell(size_t number, const MyString& str, int& rowDigitsCount) const;
public:
	ExpressionCalculator(const MyString& str, const Table* table);
	double Evaluate();
};
