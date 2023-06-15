#pragma once
#include "Row.h"
#include "..\Utilities\MyString.h"
#include "Cell\CellFactory.h"
#include "Cell\IntCell.h"
#include "Cell\DoubleCell.h"
#include "Cell\StringCell.h"
#include "Cell\FormulaCell.h"
#include "..\Utilities\SharedPtr.hpp"

class Table
{
private:
	MyVector<SharedPtr<Row>> rows;

	mutable bool errorFlag = false;
	mutable MyString errorMessage;
public:
	Table() = default;
	Table(const MyString& filePath);
	void PrintTable(std::ostream& streamType) const;
	void EditCell(size_t row, size_t column, const MyString& newData);
	const MyVector<SharedPtr<Row>>& GetRows() const;

	size_t* GetColumnsLongestWords() const;

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

