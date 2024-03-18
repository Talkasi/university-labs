from pointClass import *
from pointTable import *
import math

def getFirstNewtonDifferencesColumn(pointsTable):
	new_difference = []
	for i in range(1, len(pointsTable)):
		difference = (pointsTable[i - 1].y - pointsTable[i].y) / \
					 (pointsTable[i - 1].x - pointsTable[i].x)
		new_difference.append(difference)
	return new_difference


def getNewtonDividedDifferences(pointsTable):
	dividedDifferences = [getFirstNewtonDifferencesColumn(pointsTable)]

	for k in range(0, len(pointsTable) - 2):
		new_difference = []
		for i in range(1, len(dividedDifferences[k])):
			difference = (dividedDifferences[k][i - 1] - dividedDifferences[k][i]) / \
						 (pointsTable[i - 1].x - pointsTable[i + 1 + k].x)
			new_difference.append(difference)
		dividedDifferences.append(new_difference)

	return dividedDifferences

def expandPointsN(pointsTable, n_expand):
	new_pointsTable = []
	for point in pointsTable:
		for _ in range(n_expand):
			new_pointsTable.append(point)
	return new_pointsTable

def getFirstErmitDifferencesColumn(pointsTable):
	new_difference = []
	for i in range(1, len(pointsTable)):
		if (i - 1) % 3 == 0:
			difference = pointsTable[i - 1].first_derivative
		elif (i - 1) % 3 == 1:
			difference = pointsTable[i].first_derivative
		else:
			difference = (pointsTable[i - 1].y - pointsTable[i].y) / \
						 (pointsTable[i - 1].x - pointsTable[i].x)
		new_difference.append(difference)
	return new_difference

def getSecondErmitDifferencesColumn(pointsTable, dividedDifferences):
	new_difference = []
	for i in range(1, len(dividedDifferences)):
		if ((i - 1) % 3 != 0):
			difference = (dividedDifferences[i - 1] - dividedDifferences[i]) / \
						 (pointsTable[i - 1].x - pointsTable[i + 1].x)
			new_difference.append(difference)
		else:
			new_difference.append(pointsTable[i].second_derivative / 2)
	return new_difference

def getErmitDividedDifferences(pointsTable):
	dividedDifferences = [getFirstErmitDifferencesColumn(pointsTable)]
	dividedDifferences.append(getSecondErmitDifferencesColumn(pointsTable, dividedDifferences[0]))

	for k in range(1, len(pointsTable) - 2):
		new_difference = []
		for i in range(1, len(dividedDifferences[k])):
			difference = (dividedDifferences[k][i - 1] - dividedDifferences[k][i]) / \
						 (pointsTable[i - 1].x - pointsTable[i + 1 + k].x)
			new_difference.append(difference)
		dividedDifferences.append(new_difference)

	return dividedDifferences


def printDividedDifferences(dividedDifferences):
	for difference in dividedDifferences:
		for el in difference:
			print('{:>10.6f}'.format(el), end="\t")
		print()


def NewtonPolynom(x, pointsTable, dividedDifferences):
	y = pointsTable[0].y
	prevXDifference = x - pointsTable[0].x
	for k in range(0, len(dividedDifferences)):
		y += prevXDifference * dividedDifferences[k][0]
		prevXDifference *= (x - pointsTable[k + 1].x)
	return y


def NewtonInterpolation(pointsTable, x):
	dividedDifferences = getNewtonDividedDifferences(pointsTable)
	# printDividedDifferences(dividedDifferences)
	return NewtonPolynom(x, pointsTable, dividedDifferences)


def ErmitInterpolation(pointsTable, x):
	workPointsTable = expandPointsN(pointsTable, 3)
	dividedDifferences = getErmitDividedDifferences(workPointsTable)
	# printDividedDifferences(dividedDifferences)
	return NewtonPolynom(x, workPointsTable, dividedDifferences)


def findXPos(pointsTable, x):
	pointsTableLen = len(pointsTable)
	n_before = pointsTableLen
	n_after = 0
	for i in range(pointsTableLen):
		if pointsTable[i].x > x:
			n_before = i
			n_after = pointsTableLen - i
			break

	return n_before, n_after


def formPointsTableByXandN(pointsTable, x, n):
	if (n > len(pointsTable)):
		return None

	n_before, n_after = findXPos(pointsTable, x)
	half = round(n / 2);
	l_i = n_before - half
	r_i = n_before + (n - half)

	while (l_i < 0):
		l_i += 1
		r_i += 1

	while (r_i > len(pointsTable)):
		l_i -= 1
		r_i -= 1

	return pointsTable[l_i : r_i]


def reverseXY(pointsTable):
	pointsReversed = []
	for point in pointsTable:
		newPoint = Point(point.y, point.x, point.first_derivative, point.second_derivative)
		pointsReversed.append(newPoint)
		
	return pointsReversed

def getNewtonRoot(pointsTable):
	pointsReversed = reverseXY(pointsTable)
	return NewtonInterpolation(pointsTable, 0)


def getErmitRoot(pointsTable):
	pointsReversed = reverseXY(pointsTable)
	return ErmitInterpolation(pointsTable, 0)


def compareNEMethods(pointsTable, x, max_n = 5):
	Comparasions = []
	for n in range(max_n + 1):
		workPointsTable = formPointsTableByXandN(pointsTable, x, n)
		NewtonDividedDifferences = getNewtonDividedDifferences(workPointsTable)
		ErmitDividedDifferences = getErmitDividedDifferences(workPointsTable)
		Comparasions.append([NewtonPolynom(x, workPointsTable, NewtonDividedDifferences),
					  		 NewtonPolynom(x, workPointsTable, ErmitDividedDifferences)])
	
	return Comparasions
