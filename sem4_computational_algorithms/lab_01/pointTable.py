from pointClass import *

ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
FUCKING_GREEN='\033[0;36m'
WHITE='\033[0;37m'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

def freadPointsTable(fileName):
	pointsTable = []
	f = open(fileName, "r")
	while (line := f.readline()) != "":
		try:
			values = list(map(float, line.split()))
			values.append(0)
			values.append(0)
			pointsTable.append(Point(values[0], values[1],
									 values[2], values[3]))
		except:
			return None
	f.close()
	return pointsTable


def printPointsTable(pointsTable):
	print(WHITE, end='')
	print("┌────────────────┬────────────────┬────────────────┬────────────────┐\n"
    	  "│       X        │       Y        │       Y'       │       Y''      │\n"
    	  "├────────────────┼────────────────┼────────────────┼────────────────┤")
	for row in range(len(pointsTable)):
		curRow = pointsTable[row]
		print("│ {:14f} │ {:14f} │ {:14f} │ {:14f} │".format(curRow.x, curRow.y, 
			curRow.first_derivative, curRow.second_derivative))
	print("└────────────────┴────────────────┴────────────────┴────────────────┘")



