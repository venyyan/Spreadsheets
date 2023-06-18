#include "ExpressionCalculator.h"
#include "..\Utilities\HelperFunctions.h"

const char ROW_SYMBOL = 'R';
const char COLUMN_SYMBOL = 'C';

ArithmeticExpression* ExpressionCalculator::ParseExpression(const MyString& str) {
	if (str.GetLength() == 0) {
		return nullptr;
	}
	if (str.GetLength() == 1 && IsDigit(str[0])) {
		return new Number(str[0] - '0');
	}
	MyString strWithoutBrackets = str.SubStr(1, str.GetLength() - 2);

	size_t length = strWithoutBrackets.GetLength();
	size_t bracketsCounter = 0;

	for (size_t i = 0; i < length; i++) {
		if (strWithoutBrackets[i] == '(') {
			bracketsCounter++;
		}
		else if (strWithoutBrackets[i] == ')') {
			bracketsCounter--;
		}
		else if (IsOperator(strWithoutBrackets[i]) && bracketsCounter == 0) {
			return new Expression(
				strWithoutBrackets[i],
				ParseExpression(strWithoutBrackets.SubStr(0, i)),
				ParseExpression(strWithoutBrackets.SubStr(i + 1, length - i - 1))
			);
		}
	}
	if (str.IsInt() || str.IsDouble())
		return new Number(str.stod());
	else {
		int row = 0;
		int col = 0;

		int digitsCount = 0;
		if (str[0] == ROW_SYMBOL) {
			row = GetCell(1, str, digitsCount);
			if (digitsCount == 0)
				return new Number(0);
		}
		else {
			return new Number(0);
		}

		if (str[digitsCount + 1] == COLUMN_SYMBOL) {
			int cId = digitsCount + 1;
			col = GetCell(digitsCount + 2, str, digitsCount);
			if (cId + digitsCount != str.GetLength() - 1) {
				return new Number(0);
			}
		}
		if (row > this->table->GetRows().GetSize()
			|| col > this->table->GetRows().At(row - 1)->GetCellsCount()) {
			return new Number(0);
		}

		MyString data = this->table->GetRows().At(row - 1)->GetCells().At(col - 1)->GetData();
		if (data.IsInt() || data.IsDouble()) {
			return new Number(data.stod());
		}
		else {
			return new Number(0);
		}
	}
}

int ExpressionCalculator::GetCell(size_t startId, const MyString& str,
	int& digitsCount) const {
	char* arr = new char[str.GetLength()];
	size_t resultLen = 0;
	if (str[startId] == '0')
		return 0;

	for (size_t i = startId; i < str.GetLength(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			arr[resultLen++] = str[i];
		else
			break;
	}
	arr[resultLen] = '\0';
	digitsCount = resultLen;
	int result = MyString(arr).stoi();
	delete[] arr;
	return result;
}

ExpressionCalculator::ExpressionCalculator(const MyString& str, const Table* table)
	: table(table), expr(ParseExpression(str)) {}

double ExpressionCalculator::Evaluate() {
	return expr->Evaluate();
}