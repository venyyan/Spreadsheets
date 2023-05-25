#pragma once
#include "Cell.h"
#include "MyVector.hpp"
#include "UniquePtr.hpp"

class Row {
private:
	MyVector<UniquePtr<Cell>> cells;

public:
	Row() = default;

	void AddCell(UniquePtr<Cell>&& cell);

	void PrintRow(std::ostream& streamType) const;
};

