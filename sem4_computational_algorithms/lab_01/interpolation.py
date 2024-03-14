
def getFirstDifferencesColumn(pointsTable):
	new_difference = []
	for i in range(1, len(pointsTable)):
		difference = (pointsTable[i - 1].y - pointsTable[i].y) / \
					 (pointsTable[i - 1].x - pointsTable[i].x)
		new_difference.append(difference)
	return new_difference


def getDividedDifferences(pointsTable):
	dividedDifferences = [getFirstDifferencesColumn(pointsTable)]

	for k in range(0, len(pointsTable) - 2):
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
	dividedDifferences = getDividedDifferences(pointsTable)
	printDividedDifferences(dividedDifferences)
	return NewtonPolynom(x, pointsTable, dividedDifferences)

# def ErmitInterpolation(pointsTable, x):
# 	