from random import choice
from os import system

# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

in_test_file = "/tmp/test_in.txt"
out_test_file = "/tmp/test_out.txt"


def generate_bdouble(max_n_digits):
	n_digits = choice(range(1, max_n_digits + 1))
	res = choice(range(1, 9 + 1))
	for i in range(1, n_digits):
		res = res * 10 + choice(range(0, 9 + 1))
	return res

def generate_bint(max_n_digits):
	n_digits = choice(range(1, max_n_digits + 1))
	res = choice(range(1, 9 + 1))
	for i in range(1, n_digits):
		res = res * 10 + choice(range(0, 9 + 1))
	return res

def generate_int():
	return choice(range(0, 10))


def write_args_to_test_file(args):
	f_in = open(in_test_file, "w")
	f_in.truncate(0)
	f_in.write(args)
	f_in.close()

def read_ans_from_test_file():
	f_out = open(out_test_file, "r")
	output = f_out.readline()[:-1]
	f_out.close()
	return output


def test_passed(test_n):
	...
	# print("Test %03d: " % (test_n) + Green + "PASSED" + Color_Off)

def test_failed(test_n, args, given, expected):
	print("Test %03d: " % (test_n) + Red + "FAILED" + Color_Off)
	print("Args: ", args)
	print(Cyan + "%s - given result" % (given) + Color_Off)
	print(Blue + "%s - correct_result" % (expected) + Color_Off)


def test_main(n_tests, max_n_digits):
	for i in range(n_tests):
		d1 = generate_bdouble(max_n_digits)
		d2 = generate_bint(max_n_digits)

		args = "%.32g %.32g" % (d1, d2)
		exp = "%.31e" % (d1 / d2)

		write_args_to_test_file(args)
		system("./app.exe < " + in_test_file + " > " + out_test_file)
		res = read_ans_from_test_file()

		if (res == exp):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, exp)

def test_div(n_tests, max_n_digits):
	for i in range(n_tests):
		d1 = generate_bdouble(max_n_digits)
		d2 = generate_bint(max_n_digits)

		args = "%.32g %.32g" % (d1, d2)
		exp = "%32.32g" % (d1 / d2)

		only_significant = ""
		for char in exp:
			if char == ' ' or char == '\n':
				continue
			if char == 'e':
				break
			if char != '.' and not (only_significant == "" and char =="0"):
				only_significant += char
		only_significant = only_significant[:max_n_digits];

		write_args_to_test_file(args)
		system("./div_tester.exe < " + in_test_file + " > " + out_test_file)
		res = read_ans_from_test_file()[:max_n_digits]

		if (res == only_significant):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, only_significant)

def test_mul(n_tests, max_n_digits):
	for i in range(n_tests):
		d = generate_bdouble(max_n_digits)
		n = generate_int()

		result = "%.32g" % (d * n)

		only_significant = ""
		for char in result:
			if char == ' ' or char == '\n':
				continue
			if char == 'e':
				break
			if char != '.' and not (only_significant == "" and char =="0"):
				only_significant += char
		
		only_significant = only_significant
		args = "%d" % (d) + ' ' + "%d" % (n)

		write_args_to_test_file(args)
		system("./mul_tester.exe < " + in_test_file + " > " + out_test_file)
		output = read_ans_from_test_file()

		if (output == only_significant or int(only_significant[-1]) != (d % 10 * n % 10) % 10):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, output, only_significant)

def test_in_out(n_tests, max_n_digits):
	for i in range(n_tests):
		d = generate_bdouble(max_n_digits)
		args = "%.32g" % (d)
		exp = "%.32g" % (d)
		exp = exp

		write_args_to_test_file(args)
		system("./in_out_tester.exe < " + in_test_file + " > " + out_test_file)
		res = read_ans_from_test_file()

		if (res == exp):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, exp)

def test_cmp(n_tests, max_n_digits):
	for i in range(n_tests):
		d1 = generate_bdouble(max_n_digits)
		d2 = generate_bdouble(max_n_digits)

		args = "%.32g %.32g" % (d1, d2)

		exp = 1;
		if (d1 == d2):
			exp = 0
		elif (d1 < d2):
			exp = -1

		write_args_to_test_file(args)
		system("./cmp_tester.exe < " + in_test_file + " > " + out_test_file)
		res = int(read_ans_from_test_file())
		if res > 0:
			res = 1
		if res < 0:
			res = -1

		if (res == exp):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, exp)

def test_sub(n_tests, max_n_digits):
	for i in range(n_tests):
		d1 = generate_bdouble(max_n_digits)
		d2 = generate_bdouble(max_n_digits)

		if (d1 > d2):
			args = "%.32g %.32g" % (d1, d2)
			exp = "%.32g" % (d1 - d2)
			exp_last = (int(("%.32g" % (d1))[-1]) - int(("%.32g" % (d2))[-1])) % 10
		else:
			args = "%.32g %.32g" % (d2, d1)
			exp = "%.32g" % (d2 - d1)
			exp_last = (int(("%.32g" % (d2))[-1]) - int(("%.32g" % (d1))[-1])) % 10

		exp = exp

		write_args_to_test_file(args)
		system("./sub_tester.exe < " + in_test_file + " > " + out_test_file)
		res = read_ans_from_test_file()

		if (res == exp or int(exp[-1]) != exp_last):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, exp)


if __name__ == '__main__':
	# print(">>> IN_OUT_TESTING")
	# test_in_out(100, 32)

	# NOTE(Talkasi): There is sometimes a bug in expected big double representation.
	# It is because Python rounds big numbers in a different way.
	# So each FAILED test should be cheked before considered actually FAILED.
	# print(">>> MUL_TESTING")
	# test_mul(1000, 16)

	# print(">>> CMP_TESTING")
	# test_cmp(1000, 32)

	# print(">>> SUB_TESTING")
	# test_sub(1000, 16)

	# print(">>> DIV_TESTING")
	# test_div(1000, 14)

	print(">>> MAIN_TESTING")
	test_main(10, 32)
