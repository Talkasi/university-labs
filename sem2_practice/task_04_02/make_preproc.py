import numpy as np

cfg = open('./options.cfg', 'r')
files = cfg.readline().split()
opts = cfg.readline().split()
sizes = cfg.readline().split()
n_digits = int(cfg.readline().split()[0])
c = 0
for file in files:
        for opt in opts:
            graph_data = open(f'./data_preproc/{file}_{opt}.txt', 'w')
            for size in sizes:
                c += 1
                corrected_size = "0"*(n_digits - len(size)) + size
                data = open(f'./data/{file}_{opt}_{corrected_size}.txt')
                arr = np.array([float(i) for i in data.readlines()])
                data.close()
                mean = np.mean(arr)
                median = np.median(arr)
                minimum = np.min(arr)
                maximum = np.max(arr)
                lQuartile = np.percentile(arr, 25)
                hQuartile = np.percentile(arr, 75)
                graph_data.write(f'{size} {mean} {median} {minimum} {maximum} {lQuartile} {hQuartile}\n')
            graph_data.close()