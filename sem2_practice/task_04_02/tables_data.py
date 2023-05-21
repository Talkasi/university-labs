import numpy as np
from math import *

cfg = open('./options.cfg', 'r')
files = cfg.readline().split()
opts = cfg.readline().split()
sizes = cfg.readline().split()
n_digits = int(cfg.readline().split()[0])
c = 0
for file in files:
    for opt in opts:
        graph_data = open(f'./tables_data/{file}_{opt}.txt', 'w')
        for size in sizes:
            c += 1
            corrected_size = "0" * (n_digits - len(size)) + size
            data = open(f'./data/{file}_{opt}_{corrected_size}.txt')
            arr = np.array([float(i) for i in data.readlines()])
            data.close()
            mean = np.mean(arr)
            s = 0
            n = len(arr)
            for i in range(n):
                s += (arr[i] - mean) ** 2
            s = sqrt(s / (n - 1))
            error = s / sqrt(n)
            graph_data.write(f'{size} {mean} {error}\n')
        graph_data.close()
