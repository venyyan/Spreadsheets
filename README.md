# **Spreadsheets**

This is a program that allows you to work with data in a tabular format.

# **Data presentation**
Data from a spreadsheet is stored in a text file using the following format:

-Each line in the file represents a separate row in the table.
-Each line contains data separated by commas. These data values correspond to the cells in the row.
-Each row in the table can have a different number of cells. Therefore, each line in the file can have a different number of elements separated by commas.
-An empty line in the file represents an empty row in the table (i.e., a row where all cells are empty).
-There may be whitespace characters (empty spaces) between the data and commas in the file.

Example:
-File one: 
1,2,3,4
,,,5
-File two:
"abc",34   , "\"xyz\""

12, 12.45, 

## **Data types**

Each cell in the spreadsheet has a data type, and a table can contain cells of different types. The app supports the following data types:

-Integer: A sequence of digits without any other symbols between them. The integer can optionally start with a '+' or '-' sign.
-Float: A sequence of digits followed by a period symbol (.), and then another sequence of digits. The float can optionally start with a '+' or '-' sign.
-String: A sequence of arbitrary characters enclosed in quotation marks. To include a quotation mark within the string, it should be represented as \"
-Formula:  Formulas always start with an equal sign (=). They can involve the following operations: addition (+), subtraction (-), multiplication (*), division (/), and exponentiation (^). Formulas can include either numbers or references to cells in the spreadsheet. When a cell reference is used in a formula, its corresponding value should be used in the calculation. Grammar for a formula can be presented as: S->number|(S+S)|(S-S)|(S/S)|(S*S)|(S^S)

## **Functionalitites**

**Open**: Loads a table from a file.

**Close**: Closes the current table.

**Save**: Saves the changes to the currently opened file.

**Save as**: Saves the changes to a new file.

**Print**:  Displays the current table with alignment.

**Edit**:  Modifies the content of the specified cell. It can change the cell type to Integer, Float, String, Formula

**Exit**: Exits the app.
