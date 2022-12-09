import array
from time import time
from random import random

a = array.ArrayType('Q')

time_start = time()
for i in range(1_000_000):
    a.append(int(random() * 1_000_000_000))

time_end = time()

print("It takes {:.10f} seconds to add million random elements to the array".format((time_end - time_start)))
print("It takes ~ {:.10f} seconds to add random element\n".format((time_end - time_start) / 1_000_000))

value = int(input("Enter value of the element to add: "))

time_start = time()
a.append(value)
time_end = time()

print("It takes {:.10f} seconds to add an element using `append`".format(time_end - time_start))
time_start = time()
v = array.ArrayType('Q', [value])
time_end = time()

print("It takes {:.10f} seconds to create new array with one element".format(time_end - time_start))
print(a[-3:])

time_start = time()
a += v
time_end = time()
print(a[-3:])

print("It takes {:.10f} seconds to add an element adding array\n".format(time_end - time_start))

index, value = map(int, input(
    "Enter index of the element to change and new value of this element, separate them by space: ").split())

time_start = time()
a[index] = value
time_end = time()

print("It takes {:.10f} seconds to change an element\n".format((time_end - time_start)))

index = int(input("Enter index of the element to delete: "))

time_start = time()
a.pop(index)
time_end = time()

a.append(1_000_000)
print("It takes {:.10f} seconds to delete an element using `pop()`".format((time_end - time_start)))

time_start = time()
a = a[:index] + a[index + 1:]
time_end = time()

print("It takes {:.10f} seconds to delete an element using `[:]`".format((time_end - time_start)))
