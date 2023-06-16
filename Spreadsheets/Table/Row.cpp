#include "Row.h"

void Row::AddCell(SharedPtr<Cell>&& cell) {
	this->cells.PushBack(std::move(cell));
}

void Row::PrintRow(std::ostream& streamType, const MyVector<size_t>& columnsLongestWords) const {
	for (size_t i = 0; i < this->cells.GetSize(); i++)
	{
		size_t intervalsCount = columnsLongestWords.At(i) - this->cells.At(i)->GetData().GetLength();
		this->cells.At(i)->PrintCell(streamType);
		for (size_t i = 0; i < intervalsCount; i++)
		{
			streamType << " ";
		}
		streamType << '|';
	}
}

size_t Row::GetCellsCount() const {
	return this->cells.GetSize();
}

const MyVector<SharedPtr<Cell>>& Row::GetCells() const {
	return this->cells;
}

void Row::EditCell(SharedPtr<Cell>&& newCell, size_t at) {
	this->cells.At(at) = std::move(newCell);
}