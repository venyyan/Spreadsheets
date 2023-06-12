#include "Row.h"

void Row::AddCell(UniquePtr<Cell>&& cell) {
	this->cells.PushBack(std::move(cell));
}

void Row::PrintRow(std::ostream& streamType) const {
	for (size_t i = 0; i < this->cells.GetSize(); i++)
	{
		this->cells.At(i)->PrintCell(streamType);
		streamType << '|';
	}
}

size_t Row::GetCellsCount() const {
	return this->cells.GetSize();
}

const MyVector<UniquePtr<Cell>>& Row::GetCells() const {
	return this->cells;
}

void Row::EditCell(UniquePtr<Cell>&& newCell, size_t at) {
	this->cells.At(at) = std::move(newCell);
}