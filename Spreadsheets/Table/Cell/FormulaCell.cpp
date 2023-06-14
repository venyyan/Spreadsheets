#include "FormulaCell.h"
#include "..\..\Formula\ExpressionCalculator.h"
FormulaCell::FormulaCell() : Cell(CellType::String) {}

FormulaCell::FormulaCell(const MyString& data, const SharedPtr<const Table>& table)
	: Cell(CellType::String), data(data), table(table) {}

void FormulaCell::PrintCell(std::ostream& streamType) const {
	ExpressionCalculator expr(this->data, table);
	streamType << expr.Evaluate();
}

Cell* FormulaCell::clone() const {
	Cell* newCell = new FormulaCell(*this);
	return newCell;
}

MyString FormulaCell::GetData() const  {
	return this->data;
}