import random

def generate_bdouble():
	n_digits = random.choice(range(1, 32 + 1))
	res = random.choice(range(1, 9 + 1))
	for i in range(1, n_digits):
		res = res * 10 + random.choice(range(0, 9 + 1))
	return res

def generate_bint():
	n_digits = random.choice(range(1, 32 + 1))
	res = random.choice(range(1, 9 + 1))
	for i in range(1, n_digits):
		res = res * 10 + random.choice(range(0, 9 + 1))
	return res

for i in range(30):
	dividend = generate_bdouble()
	divisor = generate_bint()

	result = "%32.32g" % (dividend / divisor)

	only_significant = ""
	for char in result:
		if char == 'e':
			break
		if char != '.' and not (only_significant == "" and char =="0"):
			only_significant += char

	print("%32d		%32d 	 %32s" % (dividend, divisor, only_significant))
