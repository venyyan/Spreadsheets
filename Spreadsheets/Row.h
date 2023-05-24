#pragma once
#include "MyVector.hpp"
#include "UniquePtr.hpp"
#include "Cell.h"

class Row {
private:
	MyVector<UniquePtr<Cell>> cells;
	size_t cellsCount;
	size_t capacity;

public:
	Row() = default;

	void AddCell(CellType cellType);
};

