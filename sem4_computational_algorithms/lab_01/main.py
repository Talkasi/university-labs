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
	n_nodes = int(input("Enter n nodes: "))
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

	NewtonY = NewtonInterpolation(workPointsTable, x)
	# ErmitY = ErmitInterpolation(pointsTable, x)
	print(BLUE, "NewtonY: ", end='')
	print(WHITE, NewtonY, end='')
	

	print(NC)


if __name__ == "__main__":
	main()