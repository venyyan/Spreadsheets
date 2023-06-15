#include "FormulaCell.h"
#include "..\..\Formula\ExpressionCalculator.h"
FormulaCell::FormulaCell() : Cell(CellType::Formula) {}

FormulaCell::FormulaCell(const MyString& data)
	: Cell(CellType::Formula), data(data) {}

void FormulaCell::PrintCell(std::ostream& streamType) const {
	
}

Cell* FormulaCell::clone() const {
	Cell* newCell = new FormulaCell(*this);
	return newCell;
}

MyString FormulaCell::GetData() const {
	return this->data;
}