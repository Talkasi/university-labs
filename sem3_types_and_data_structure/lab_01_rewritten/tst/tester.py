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
	print("Test %03d: " % (test_n) + Green + "PASSED" + Color_Off)

def test_failed(test_n, args, given, expected):
	print("Test %03d: " % (test_n) + Red + "FAILED" + Color_Off)
	print("Args: ", args)
	print(Cyan + "%s - given result" % (given) + Color_Off)
	print(Blue + "%32s - correct_result" % (expected) + Color_Off)


def test_div_bdoubles(n_tests, max_n_digits):
	for i in range(n_tests):
		dividend = generate_bdouble(max_n_digits)
		divisor = generate_bint(max_n_digits)

		result = "%32.32g" % (dividend / divisor)

		only_significant = ""
		for char in result:
			if char == 'e':
				break
			if char != '.' and not (only_significant == "" and char =="0"):
				only_significant += char

		print("%32d		%32d 	 %32s 	 %.32e" % (dividend, divisor, only_significant, dividend / divisor))

def test_mul_bdouble(n_tests, max_n_digits):
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
		
		only_significant = only_significant + (32 - len(only_significant)) * '0'
		args = "%d" % (d) + ' ' + "%d" % (n)

		write_args_to_test_file(args)
		system("./mul_tester.exe < " + in_test_file + " > " + out_test_file)
		output = read_ans_from_test_file()

		if (output == only_significant):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, output, only_significant)

def test_in_out(n_tests, max_n_digits):
	for i in range(n_tests):
		d = generate_bdouble(max_n_digits)
		args = "%.32g" % (d)
		exp = "%.32g" % (d)
		exp = exp + (max_n_digits - len(exp)) * '0'

		write_args_to_test_file(args)
		system("./in_out_tester.exe < " + in_test_file + " > " + out_test_file)
		res = read_ans_from_test_file()

		if (res == exp):
			test_passed(i + 1)
		else:
			test_failed(i + 1, args, res, exp)

if __name__ == '__main__':
	test_in_out(100, 32)
	# NOTE(Talkasi): There is sometimes a bug in expected big double representation.
	# It is because Python rounds big numbers in a different way.
	# So each FAILED test should be cheked before considered actually FAILED.
	test_mul_bdouble(100, 16)

