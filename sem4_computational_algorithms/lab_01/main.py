from pointTable import *
from interpolation import *

ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
FUCKING_GREEN='\033[0;36m'
WHITE='\033[0;37m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

def main():
	pointsTable = freadPointsTable("CA_lab1_data.txt")
	if (pointsTable == None):
		print(RED, "Error: Wrong file!", NC)
		return

	n = int(input("Enter n: "))
	x = float(input("Enter x: "))

	print(BLUE, end='')
	print("Table of points from the file: ")
	printPointsTable(pointsTable)

	workPointsTable = formPointsTableByXandN(pointsTable, x, n + 1)
	if (workPointsTable == None):
		print(RED, "Error: Wrong n!", NC)
		return

	print(BLUE, "Table of points to work with (n): ")
	printPointsTable(workPointsTable)

	print("\n────────────── Interpolation ──────────────")
	NewtonY = NewtonInterpolation(workPointsTable, x)
	print(BLUE, "NewtonY: ", end='')
	print(WHITE, NewtonY)
	ErmitY = ErmitInterpolation(workPointsTable, x)
	print(BLUE, "ErmitY: ", end='')
	print(WHITE, ErmitY)


	print("\n───────── Reversed interpolation ──────────")
	NewtonRoot = getNewtonRoot(workPointsTable)
	print(BLUE, "NewtonRoot: ", end='')
	print(WHITE, NewtonRoot)
	ErmitRoot = getErmitRoot(workPointsTable)
	print(BLUE, "ErmitRoot: ", end='')
	print(WHITE, ErmitRoot)

	compareTable = get_compare_Newton_Ermite(points, x)
	print("Compare table:")
	io.print_compare_table(compare_table)


	print("\n\n--------Solving nonlinear equations--------\n")

	data_func_1_y_x = [
	    Point(0.005, 0.137, None, None),
	    Point(0.035, 0.343, None, None),
	    Point(0.055, 0.421, None, None),
	    Point(0.065, 0.454, None, None),
	    Point(0.135, 0.626, None, None),
	    Point(0.155, 0.664, None, None),
	    Point(0.195, 0.731, None, None),
	    Point(0.275, 0.843, None, None),
	    Point(0.315, 0.891, None, None),
	    Point(0.405, 0.985, None, None),
	]

	data_func_2_x_y = [
	    Point(0.1, -0.284, None, None),
	    Point(0.3, -0.300, None, None),
	    Point(0.4, -0.293, None, None),
	    Point(0.48, -0.266, None, None),
	    Point(0.6, -0.165, None, None),
	    Point(0.68, -0.037, None, None),
	    Point(0.75, 0.128, None, None),
	    Point(0.88, 0.610, None, None),
	    Point(0.95, 0.988, None, None),
	    Point(1.03, 1.547, None, None),
	]

	data_func_1_x_y = get_rev_data(data_func_1_y_x)

	new_data_func_1_x_y = []

	for point in data_func_2_x_y:
	    index = get_index(data_func_1_x_y, point.x)
	    working_points = get_works_points(data_func_1_x_y, index, n)

	    newton_table = get_newton_table(working_points)
	    new_data_func_1_x_y.append(Point(
	        point.x, get_approximate_value(newton_table, point.x, n), None, None))

	print("data_1")
	io.print_two_cols_table(new_data_func_1_x_y)
	print("data_2")
	io.print_two_cols_table(data_func_2_x_y)

	new_data = []
	for i in range(len(new_data_func_1_x_y)):
	    new_data.append(Point(
	        new_data_func_1_x_y[i].x, new_data_func_1_x_y[i].y - data_func_2_x_y[i].y, None, None))
	    
	print("new data")
	io.print_two_cols_table(new_data)

	solve = get_root_by_Newton(new_data, n)
	print("Solve: ", solve)

	print(NC)


if __name__ == "__main__":
	main()