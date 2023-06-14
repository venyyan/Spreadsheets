#pragma once
#include "Cell.h"
#include "..\..\Utilities\MyString.h"
#include "..\..\Utilities\SharedPtr.hpp"
#include "..\Table.h"
class Table;
class FormulaCell : public Cell
{
private:
	MyString data;
	SharedPtr<const Table> table = nullptr;
public:
	FormulaCell();
	FormulaCell(const MyString& data, const SharedPtr<const Table>& table);

	void PrintCell(std::ostream& streamType) const override;

	Cell* clone() const override;

	virtual MyString GetData() const override;
};
