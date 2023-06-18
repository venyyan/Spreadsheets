#include "IntCell.h"
#include "..\..\Utilities\HelperFunctions.h"

IntCell::IntCell(int data) : Cell(CellType::Int), data(data) {}

IntCell::IntCell() : Cell(CellType::Int) {}

Cell* IntCell::Clone() const  {
	Cell* newCell = new IntCell(*this);
	return newCell;
}

MyString IntCell::GetData() const {
	return IntToString(this->data);
}

void IntCell::PrintCell(std::ostream& streamType) const {
	streamType << this->data;
}