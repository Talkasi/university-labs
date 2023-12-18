import networkx as nx
import numpy as np
import random

graph_size = 7
possibility = 0.3

matrix = [[0] * graph_size for _ in range(graph_size)]


for i in range(graph_size):
    for j in range(i + 1, graph_size):
        if random.random() < possibility:  
            matrix[i][j] = 1
            matrix[j][i] = 1


for row in matrix:
    print(' '.join(map(str, row)))
