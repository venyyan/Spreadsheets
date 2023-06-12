#pragma once
#include "Cell\Cell.h"
#include "..\Utilities\MyVector.hpp"
#include "..\Utilities\UniquePtr.hpp"
#include "..\Utilities\MyString.h"

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

