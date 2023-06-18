#include <iostream>
#include "..\Table\Table.h"
#include "..\Formula\ExpressionCalculator.h"

void Run() {
	std::cout << "You're using Spreadsheets!";

	while (true) {
		std::cout << "Enter a file path to open a table: "
			<< std::endl;
		MyString filePath;
		std::cin >> filePath;
		SharedPtr<Table> table(new Table(filePath));
		if (table->GetErrorFlag()) {
			std::cout << table->GetErrorMessage();
			return;
		}
		std::cout << "Opening table from " << filePath << std::endl;
		table->PrintTable(std::cout);
		std::cout << "Enter a command:"
			"\nedit - edit a cell"
			"\nprint - print the table"
			"\nclose - close the current table"
			"\nsave - save the table"
			"\nsave as - save the table in a desired format"
			"\nexit - exit Spreadsheets" << std::endl;

		while (true) {
			std::cout << "Enter another command: ";
			MyString command;
			std::cin >> command;

			if (command == "edit") {
				std::cout << "Enter a row: " << std::endl;
				size_t row;
				std::cin >> row;

				std::cout << "Enter a column: " << std::endl;
				size_t column;
				std::cin >> column;

				std::cin.ignore();
				std::cout << "Enter new data: " << std::endl;
				MyString newData;
				std::cin >> newData;
				try {
					table->EditCell(row, column, newData);
					std::cout << "row " << row << " column " << column
						<< " edited successfully!" << std::endl;
 				}
				catch (std::invalid_argument& exc) {
					std::cout << exc.what() << std::endl;
				}

			}
			else if (command == "print") {
				table->PrintTable(std::cout);
			}
			else if (command == "close") {
				std::cout << "Closing current table..." << std::endl;
				break;
			}
			else if (command == "save as") {
				std::cout << "Enter a file name to save table: ";
				MyString filePath;
				std::cin >> filePath;
				table->SaveTable(filePath);
				std::cout << "Table saved successfully!" << std::endl;
			}
			else if (command == "save") {
				table->SaveTable("file.txt");
				std::cout << "Table saved successfully!" << std::endl;
			}
			else if (command == "exit")
				return;
		}
	}
}
int main()
{
	Run();
}