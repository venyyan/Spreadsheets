#pragma once
#include "Row.h"
#include "..\Utilities\MyString.h"
#include "..\Utilities\SharedPtr.hpp"
#include "Cell\IntCell.h"
#include "Cell\DoubleCell.h"
#include "Cell\StringCell.h"
#include "Cell\FormulaCell.h"

class Table {
private:
	MyVector<SharedPtr<Row>> rows;

	mutable bool errorFlag = false;
	mutable MyString errorMessage;
public:
	Table() = default;
	Table(const MyString& filePath);

	void PrintTable(std::ostream& streamType) const;
	void EditCell(size_t row, size_t column, const MyString& newData);
	void SaveTable(const MyString& filePath) const;

	const MyVector<SharedPtr<Row>>& GetRows() const;
	MyVector<size_t> GetColumnsLongestWords() const;
	bool GetErrorFlag() const;
	const MyString& GetErrorMessage() const;

private:
	void GetTableFromFile(const MyString& filePath);
	SharedPtr<Row> ReadRow(std::ifstream& ifs) const;
	SharedPtr<Cell> ReturnCell(const MyString& cellStr) const;

	size_t GetLongestRow() const;
	void AddEmptyCells(size_t longestRow);
	void EvaluateFormulas();
};

