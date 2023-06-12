#include "IntCell.h"

IntCell::IntCell(int data) : Cell(CellType::Int), data(data) {}

IntCell::IntCell() : Cell(CellType::Int) {}


Cell* IntCell::clone() const  {
	Cell* newCell = new IntCell(*this);
	return newCell;
}

int IntCell::GetData() const {
	return this->data;
}

void IntCell::PrintCell(std::ostream& streamType) const {
	streamType << this->data;
}