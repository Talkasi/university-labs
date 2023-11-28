import random
import string

characters = string.ascii_letters + string.digits + './ '
def generate_flat():
	addr_len = random.randint(1, 50)
	addr = ''.join(random.choice(characters) for _ in range(addr_len))
	area = random.randint(1, 999999)
	n_rooms = random.randint(1, 20)
	cost_per_square = random.randint(1000, 1000000)
	housing_type = random.randint(1, 2)

	if housing_type == 1:
		decoration = random.randint(0, 1)
		return [addr, area, n_rooms, cost_per_square, housing_type, decoration]
	else:
		year = random.randint(1970, 2023)
		n_prev_owners = random.randint(1, 99)
		animals = random.randint(0, 1)
		return [addr, area, n_rooms, cost_per_square, housing_type, year, n_prev_owners, animals]


test_n = 50
for test in range(test_n):
	n = str(test + 1)
	if (len(n) == 1):
		n = '0' + n

	file_name = "dbs/tests/db_" + n + ".txt"
	with open(file_name, 'w') as f:
		if (test < test_n / 5):
			records_n = 20
		elif (test < test_n / 5 * 2):
			records_n = 40
		elif (test < test_n / 5 * 3):
			records_n = 100
		elif (test < test_n / 5 * 4):
			records_n = 500
		else:
			records_n = 1000

		list = []
		for _ in range(records_n):
			line = generate_flat()
			list.append(line)
			line = ','.join(str(line[i]) for i in range(len(line))) + ',\n'
			f.write(line)

		list.sort(key = lambda x: x[3])
		# print(list)
		file = "dbs/tests/db_" + n + "_sorted.txt"
		with open(file, 'w') as f_s:
			for i in range(records_n):
				# print(','.join(str(list[i][j]) for j in range(len(list[i]))) + ',\n')
				f_s.write(','.join(str(list[i][j]) for j in range(len(list[i]))) + ',\n')
