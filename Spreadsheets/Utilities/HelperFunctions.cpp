#include "HelperFunctions.h"

int Pow(int a, int b) {
	double result = 1;
	if (b >= 0) {
		for (int i = 0; i < b; ++i) {
			result *= a;
		}
	}
	else {
		for (int i = 0; i < -b; ++i) {
			result /= a;
		}
	}
	return result;
}

bool IsOperator(char op) {
	return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

bool IsDigit(char c) {
	return c >= '0' && c <= '9';
}

size_t GetNumberSize(int number) {
	int numberSize = 0;

	if (number == 0) {
		numberSize = 1;
	}
	while (number > 0) {
		number /= 10;
		numberSize++;
	}
	return numberSize;
}

MyString IntToString(int number) {
	if (number == 0)
		return MyString("0");

	size_t ind = 0;
	size_t size = 0;
	int numCopy = number;
	while (numCopy != 0) {
		numCopy /= 10;
		size++;
	}
	char* result = new char[size + 2] {};
	if (number < 0) {
		result[ind++] = '-';
		number = -number;
	}
	ind += size - 1;
	for (int i = size - 1; i >= 0; i--)
	{
		result[ind--] = number % 10 + '0';
		number /= 10;
	}
	MyString strResult(result);
	delete[] result;
	return strResult;
}

MyString DoubleToString(double number) {
	MyString wholePart = IntToString(number);

	double mantissa = number - (int)number;

	int precision = 6;
	char* result = new char[precision + 2] {};
	result[0] = '.';
	for (size_t i = 0; i < precision; i++)
	{
		mantissa *= 10;
		result[i + 1] = (int)mantissa + '0';
		mantissa -= (int)mantissa;
	}

	wholePart += MyString(result);
	size_t removeCount = 0;
	for (int i = wholePart.GetLength() - 1; i >= 0; i--)
	{
		if (wholePart[i] != '0')
			break;

		if (wholePart[i] == '0')
			removeCount++;
	}

	if (wholePart[wholePart.GetLength() - 1 - removeCount] == '.')
		removeCount++;
	return wholePart.SubStr(0, wholePart.GetLength() - removeCount);
}
