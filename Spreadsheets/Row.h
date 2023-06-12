#pragma once
#include "Cell.h"
#include "MyVector.hpp"
#include "UniquePtr.hpp"
#include "MyString.h"

class Row {
private:
	MyVector<UniquePtr<Cell>> cells;

public:
	Row() = default;

	size_t GetCellsCount() const;

	const MyVector<UniquePtr<Cell>>& GetCells() const;

	void AddCell(UniquePtr<Cell>&& cell);

	void PrintRow(std::ostream& streamType) const;

	void EditCell(UniquePtr<Cell>&& newCell, size_t at);
};

