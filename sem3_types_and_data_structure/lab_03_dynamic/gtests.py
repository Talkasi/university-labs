from random import randint
import struct

for i in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 50, 100]:
	for j in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 50, 100]:
		for r in [5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 95, 98, 99, 100]:
			fname = "tests/" + str(i) + "x" + str(j) + "p" + str(r)
			f = open(fname + ".bin", "wb");
			g = open (fname + ".txt", "w");

			f.write(struct.pack("l", i) + struct.pack("l", j))
			g.write(str(i)+ " "+ str(j) + "\n")
			for a in range(i):
				for b in range(j):
					n = randint(-10000, 10000) * randint(-1, 1) * randint(-1, 0)
					f.write(struct.pack("i", n))
					g.write(str(n) + " ")
				g.write("\n")

			f.close()
			g.close()

