#include "IntCell.h"

IntCell::IntCell(int data) : Cell(CellType::Int), data(data) {}

//void IntCell::PrintCell() const  {
//	
//}

Cell* IntCell::clone() const  {
	Cell* newCell = new IntCell(*this);
	return newCell;
}

int IntCell::GetData() const {
	return this->data;
}
