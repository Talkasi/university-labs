import tkinter

import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

import logic
from tkinter.ttk import Treeview


def plot(a, b):
    fig = Figure(figsize=(14, 4))
    graph = fig.add_subplot()

    x = np.linspace(a, b)
    y = np.array([logic.f(x_i) for x_i in x])

    y1 = np.diff(y)
    y2 = np.diff(y1)

    zeroes = np.abs(y) < 1e-8
    extrms = np.abs(y1) < 1e-8
    inferp = np.abs(y2) < 1e-9

    graph.plot(x, y)

    graph.scatter(x[:-1][extrms], y[:-1][extrms], color='green', s=40, marker='o', label="Extremes")
    graph.scatter(x[:-2][inferp], y[:-2][inferp], color='red', s=40, marker='o', label="Inflection points")
    graph.scatter(x[zeroes], y[zeroes], color='orange', s=20, marker='o', label="Zeros")

    graph.legend()
    graph.grid()
    graph.set_ylabel("cos(x)")
    graph.set_xlabel("x")

    canvas = FigureCanvasTkAgg(fig)
    canvas.draw()
    canvas.get_tk_widget().grid(pady=10)


root = tkinter.Tk()

tkinter.Label(text="COS(X)", font="20").grid()

table = Treeview()
table.grid()
headers = ["№", "[xi; xi+1]", "x’", "f(x’)", "Iterations number", "Error key"]
table["columns"] = headers

iterations = logic.find_iterations(-1, 1, 0.5)
if iterations == "Error":
    print("FATAL ERROR")
    exit(1)

data = []
for i in range(len(iterations)):
    data.append(logic.chords_clarification(iterations[i][0], iterations[i][1], 0.01, 1000))

for header in headers:
    table.heading(header, text=header, anchor='center')
for row in data:
    table.insert("", tkinter.END, values=row)

plot(-1, 1)

root.mainloop()
