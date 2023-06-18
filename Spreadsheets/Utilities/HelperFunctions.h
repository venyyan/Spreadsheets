#pragma once
#include "MyString.h"

int Pow(int a, int b);
bool IsOperator(char op);
bool IsDigit(char ch);
size_t GetNumberSize(int number);

MyString IntToString(int number);
MyString DoubleToString(double number);