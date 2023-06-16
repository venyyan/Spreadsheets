#include "HelperFunctions.h"

int Pow(int a, int b)
{
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

bool IsOperator(char op)
{
	return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

bool IsDigit(char c) {
	return c >= '0' && c <= '9';
}

size_t GetNumberSize(int number)
{
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
