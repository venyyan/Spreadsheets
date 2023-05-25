#include "CellFactory.h"

Cell* CellFactory(CellType cellType)
{
	switch (cellType)
	{
	case CellType::Int:
		return new IntCell();
	case CellType::Double:
		return new DoubleCell();
	}
	return nullptr;
}