#pragma once
#include "Cell\Cell.h"
#include "..\Utilities\MyVector.hpp"
#include "..\Utilities\SharedPtr.hpp"
#include "..\Utilities\MyString.h"

class Row {
private:
	MyVector<SharedPtr<Cell>> cells;

public:
	Row() = default;

	size_t GetCellsCount() const;

	const MyVector<SharedPtr<Cell>>& GetCells() const;

	void AddCell(SharedPtr<Cell>&& cell);

	void PrintRow(std::ostream& streamType, size_t* columnsLongestWords) const;

	void EditCell(SharedPtr<Cell>&& newCell, size_t at);
};

