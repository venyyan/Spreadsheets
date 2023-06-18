#include "Table.h"
#include <fstream>
#include <sstream>
#include <exception>
#include "..\Formula\ExpressionCalculator.h"
#include "..\Utilities\HelperFunctions.h"

const int CELL_MAX_SIZE = 100;

Table::Table(const MyString& filePath) {
	GetTableFromFile(filePath);
}

void Table::GetTableFromFile(const MyString& filePath) {
	std::ifstream file(filePath.c_str());

	if (!file.is_open()) {
		this->errorFlag = true;
		this->errorMessage = "Error: cannot open file!";
		return;
	}

	MyVector<SharedPtr<Row>> rows;

	while (true) {
		if (file.eof())
			break;

		SharedPtr<Row> currentRow = ReadRow(file);
		if (!currentRow)
			return;
		rows.PushBack(std::move(currentRow));
	}
	this->rows = std::move(rows);

	size_t longestRow = GetLongestRow();
	AddEmptyCells(longestRow);
	EvaluateFormulas();
}

SharedPtr<Row> Table::ReadRow(std::ifstream& ifs) const {
	MyString rowBuffer;
	ifs >> rowBuffer;

	SharedPtr<Row> currentRow(new Row());
	if (rowBuffer.IsEmpty()) {
		currentRow->AddCell(new StringCell(""));
		return currentRow;
	}
	
	std::stringstream ss(rowBuffer.c_str());
	size_t cellsCount = 0;

	while (!ss.eof()) {
		char cellBuffer[CELL_MAX_SIZE];
		ss.getline(cellBuffer, CELL_MAX_SIZE, ',');

		MyString cellStr(cellBuffer);
		SharedPtr<Cell> cell = ReturnCell(cellStr);
		if (!cell) {
			this->errorFlag = true;
			this->errorMessage = "Error! Unknown cell type!";
			return nullptr;
		}
		currentRow->AddCell(std::move(cell));
	}
	return currentRow;
}

SharedPtr<Cell> Table::ReturnCell(const MyString& cellStr) const {
	if (cellStr.IsInt()) {
		return new IntCell(cellStr.stoi());
	}
	else if (cellStr.IsDouble()) {
		return new DoubleCell(cellStr.stod());
	}
	else if (cellStr.IsQuote()) {
		return new StringCell(cellStr.ExtractQuote());
	}
	else if (cellStr.IsFormula()) {
		return new FormulaCell(cellStr.ExtractFormula());
	}
	else if (cellStr.IsEmptyString()) {
		return new StringCell("");
	}
	else {
		return nullptr;
	}
}

size_t Table::GetLongestRow() const {
	size_t longestRow = 0;
	for (size_t i = 0; i < this->rows.GetSize(); i++) {
		size_t currentRowSize = this->rows.At(i)->GetCellsCount();
		if (currentRowSize > longestRow)
			longestRow = currentRowSize;
	}
	return longestRow;
}

void Table::AddEmptyCells(size_t longestRow) {
	for (size_t i = 0; i < this->rows.GetSize(); i++) {
		size_t currentRowSize = this->rows.At(i)->GetCellsCount();
		if (currentRowSize < longestRow) {
			int emptyCellsCount = longestRow - this->rows.At(i)->GetCellsCount();
			for (size_t j = 0; j < emptyCellsCount; j++) {
				SharedPtr<Cell> cell = new StringCell("");
				this->rows.At(i)->AddCell(std::move(cell));
			}
		}
	}
}

void Table::EvaluateFormulas() {
	for (size_t i = 0; i < this->rows.GetSize(); i++) {
		size_t currentRowSize = this->rows.At(i)->GetCellsCount();
		for (size_t j = 0; j < currentRowSize; j++) {
			if (this->rows.At(i)->GetCells().At(j)->GetType() == CellType::Formula) {
				ExpressionCalculator expr(this->rows.At(i)->GetCells().At(j)->GetData(), this);
				try {
					double evaluated = expr.Evaluate();
					SharedPtr<Cell> edited = new DoubleCell(evaluated);
					this->rows.At(i)->EditCell(std::move(edited), j);
				}
				catch (std::logic_error& exc) {
					SharedPtr<Cell> edited = new StringCell("ERROR");
					this->rows.At(i)->EditCell(std::move(edited), j);
				}
			}
		}
	}
}

bool Table::GetErrorFlag() const {
	return this->errorFlag;
}

const MyString& Table::GetErrorMessage() const {
	return this->errorMessage;
}

void Table::PrintTable(std::ostream& streamType) const {
	MyVector<size_t> columnsLongestWords = GetColumnsLongestWords();
	for (size_t i = 0; i < this->rows.GetSize(); i++) {
		this->rows.At(i)->PrintRow(streamType, columnsLongestWords);
		streamType << std::endl;
	}
}

void Table::EditCell(size_t row, size_t column, const MyString& newData) {
	if (row > this->GetRows().GetSize()) {
		MyString errorMessage = "ERROR: There is no row " + IntToString(row);
		throw std::invalid_argument(errorMessage.c_str());
	}
	if (column > this->GetRows().At(row - 1)->GetCellsCount()) {
		MyString errorMessage = "ERROR: There is no column " + IntToString(column);
		throw std::invalid_argument(errorMessage.c_str());
	}

	if (!newData.IsDouble() && !newData.IsFormula() && !newData.IsInt()
		&& !newData.IsQuote()) {
		MyString errorMessage = "ERROR: " + newData + " is unknown data type!";
		throw std::invalid_argument(errorMessage.c_str());
	}

	SharedPtr<Cell> edited = ReturnCell(newData);
	if (edited->GetType() == CellType::Formula) {
		ExpressionCalculator expr(edited->GetData(), this);
		try {
			double evaluated = expr.Evaluate();
			edited = new DoubleCell(evaluated);
		}
		catch (std::logic_error& exc) {
			edited = new StringCell("ERROR");
		}
	}
	this->rows.At(row - 1)->EditCell(std::move(edited), column - 1);
}

void Table::SaveTable(const MyString& filePath) const
{
	std::ofstream ofs(filePath.c_str());
	this->PrintTable(ofs);
	ofs.close();
}

const MyVector<SharedPtr<Row>>& Table::GetRows() const {
	return this->rows;
}

MyVector<size_t> Table::GetColumnsLongestWords() const
{
	MyVector<size_t> longestWords;
	size_t columnsCount = this->rows.At(0)->GetCellsCount();
	for (size_t i = 0; i < columnsCount; i++) {
		size_t longestWordLen = 0;
		for (int j = 0; j < this->rows.GetSize(); j++) {
			if (this->rows.At(j)->GetCells().At(i)->GetData().GetLength() > longestWordLen)
				longestWordLen = this->rows.At(j)->GetCells().At(i)->GetData().GetLength();
		}
		longestWords.At(i) = longestWordLen;
	}
	return longestWords;
}