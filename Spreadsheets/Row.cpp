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