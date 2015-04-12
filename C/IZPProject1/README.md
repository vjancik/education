#IZP Project 1

###Assignment

Implement a simple tabular calculator. The program will be able to calculate maximum, minimum, sum, mean of a selection of cells. The table in the form of a text file will be expected on the standard input. The requested operation and the selection of cells will be specified by the user through command line arguments.

**Program arguments**
- `--help` prints out help (in Slovak)
- \<operation\> can be one of the following operations
  - `select`, prints the selected cells
  - `min`, selects the smallest value out of all cells in range
  - `max`, the biggest
  - `sum`, the sum of the cells in range
  - `avg`, the average of the cells
- \<cell_range\> represents the range of the cells for the operation to be executed on
  - `row X`, selects all cells at row X
  - `col X`, selects all cells at column X
  - `rows X Y`, selects the cells from the range of rows from X to Y
  - `cols X Y`, selects the cells from the range of columns from X to Y
  - `range A B X Y`, selects the cells from the range of rows from A to B and the range of columns from X to Y

*Note: The code for this project is written in Slovak.*
