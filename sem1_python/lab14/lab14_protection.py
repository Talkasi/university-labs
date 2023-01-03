import struct

val_type = "20s20sQQ20s"
val_size = struct.calcsize(val_type)

with open("in.bin", "wb") as file:
    n = int(input("Enter number of records you want to write to database: "))
    for i in range(n):
        print("\nNew record\n")
        country = input("Enter country name: ")
        while len(country) < 1:
            print("Error. Name of the country should not be an empty string.")
            country = input("Enter country name: ")

        continent = input("Enter continent name: ")
        while len(continent) < 1:
            print("Error. Name of the continent should not be an empty string.")
            continent = input("Enter continent name: ")

        s = int(input("Enter s of a country: "))
        people = int(input("Enter number of people in the country: "))
        vvp = input("Enter vvp: ")
        while not vvp.isdigit():
            print("Error. vvp is a string of digits.")
            vvp = input("Enter vvp: ")

        file.write(
            struct.pack(val_type, country.encode("utf-8"), continent.encode("utf-8"), s, people, vvp.encode("utf-8")))

file = open("in.bin", "rb")
file.seek(0, 2)
file_size = file.tell()

if file_size == 0:
    print("Error. The first file is empty.")
    exit()

file.seek(0, 0)
n = 1
print("\nThe first file")
for i in range(0, file_size, val_size):
    record = list(struct.unpack(val_type, file.read(val_size)))
    print("\nRecord #{:g}:".format(n))
    print("Country: ", record[0].decode("utf-8"))
    print("continent: ", record[1].decode("utf-8"))
    print("S:", record[2])
    print("Number of people:", record[3])
    print("VVP:", record[4].decode("utf-8"))
    n += 1

file.seek(0, 0)
file_out = open("out.bin", "w+b")
for i in range(0, file_size, val_size):
    record = list(struct.unpack(val_type, file.read(val_size)))
    if record[2] >= 3000000 and record[3] >= 25000000:
        file_out.write(struct.pack("20sQQ", record[0], record[2], record[3]))

file.close()

file_out.seek(0, 2)
file_size = file_out.tell()
if file_size == 0:
    print("The second file is empty.")
else:
    file_out.seek(0, 0)
    n = 1
    print("\nThe second file")
    for i in range(0, file_size, struct.calcsize("20sQQ")):
        record = list(struct.unpack("20sQQ", file_out.read(struct.calcsize("20sQQ"))))
        print("\nRecord #{:g}:".format(n))
        print("Country: ", record[0].decode("utf-8"))
        print("S:", record[1])
        print("Number of people:", record[2])
        n += 1

file_out.close()
