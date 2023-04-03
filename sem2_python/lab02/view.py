from tkinter import messagebox as box
from tkinter.ttk import Treeview
import tkinter

import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

import logic
from math import *

entries = []
bg_color = "gray22"
fg_color = "white"
input_bg_color = "gray32"


def create_input_field(master_field, label_text, input_check):
    working_field = tkinter.Frame(master=master_field, bg=bg_color)
    tkinter.Label(master=working_field, text=label_text, bg=bg_color, fg=fg_color,
                  width=25, font='Calibri 14').grid(column=0, row=0, pady=10)

    entry = tkinter.Entry(master=working_field, bg=input_bg_color, fg="yellow", width=25, justify="center")

    if input_check is not None:
        reg = root.register(input_check)
        entry.config(validate="key", validatecommand=(reg, "%P"))

    entries.append(entry)
    entry.grid(column=1, row=0, pady=10)
    working_field.grid()


def n_checker(_type, _sign):
    def checker(text):
        if len(text) == 0:
            return True

        s_exp = (text[0] in "+-") if _sign else (text[0] == "+")
        if (text[-1] in "Ee" and sum(text.count(i) for i in "Ee") <= 1) or len(text) == 1 and s_exp:
            return True

        if _type == "float":
            try:
                float(text)
                warning_label.config(text="")
            except:
                warning_label.config(text="Warning: wrong input.")
                return False
        else:
            try:
                int(text)
                warning_label.config(text="")
            except:
                warning_label.config(text="Warning: wrong input.")
                return False

        return True

    return checker


def start_computing():
    warning_label.config(text="")

    function = entries[0].get()

    if len(function) == 0:
        warning_label.config(text="Warning: there is an empty field.")
        return 0

    if logic.evaluate(1, function) == "Error":
        warning_label.config(text="Warning: wrong function.")
        return 0

    parameters = []

    for i in range(1, len(entries)):
        parameters += [entries[i].get()]
        if len(parameters[i - 1]) == 0:
            warning_label.config(text="Warning: there is an empty field.")
            return 0

    start = float(parameters[0])
    end = float(parameters[1])
    step = float(parameters[2])
    eps = float(parameters[3])
    n_max = int(parameters[4])

    # Check if start of the segment is bigger than the end
    if start > end:
        warning_label.config(text="Warning: wrong segment.")
        return 0

    if step <= 0:
        warning_label.config(text="Warning: wrong step.")
        return 0

    if eps <= 0 or eps > 1:
        warning_label.config(text="Warning: wrong eps.")
        return 0

    if n_max <= 0:
        warning_label.config(text="Warning: wrong max number of iterations.")
        return 0

    intervals = logic.find_intervals(start, end, step, function)
    if intervals == "Error":
        warning_label.config(text="Warning: can't compute function.")
        return 0

    n = 0
    data = []
    for start_i, end_i in intervals:
        data.append(logic.clarification(function, start_i, end_i, n_max, eps, n))
        n += 1

    table = Treeview()
    table.grid(row=1, column=0, columnspan=6, pady=50)
    headers = ["№", "[xi; xi+1]", "x’", "f(x’)", "Iterations number", "Error key"]
    table["columns"] = headers

    for header in headers:
        table.heading(header, text=header, anchor='center')
    for row in data:
        table.insert("", tkinter.END, values=row)

    graph(start, end, function)


def graph(start, end, function):
    fig = Figure(figsize=(8, 4))
    a_f = fig.add_subplot()

    x_es = np.linspace(start, end, int((end - start) * 1000))
    y_es = np.array([logic.evaluate(i, function) for i in x_es])

    y_d1 = np.diff(y_es)
    y_d2 = np.diff(y_d1)

    zeros = np.abs(y_es) < 1e-3
    extremes = np.abs(y_d1) < 1e-5
    inflection = np.abs(y_d2) < 1e-8

    a_f.plot(x_es, y_es)

    a_f.scatter(x_es[:-1][extremes], y_es[:-1][extremes], color='green', s=40, marker='o', label="extremes")
    a_f.scatter(x_es[:-2][inflection], y_es[:-2][inflection], color='red', s=40, marker='o', label="inflection points")
    a_f.scatter(x_es[zeros], y_es[zeros], color='orange', s=20, marker='o', label="zeros")

    a_f.legend()
    a_f.grid()
    a_f.set_ylabel(function)
    a_f.set_xlabel("x")
    canvas = FigureCanvasTkAgg(fig)
    canvas.draw()
    canvas.get_tk_widget().grid(row=0, column=1, columnspan=4, padx=40, pady=10)


def error_keys():
    box.showinfo('Error keys',
                 "0 - no errors occurred;\n"
                 "1 - too many iterations.\n")


root = tkinter.Tk()

root.geometry('1400x830')
root.resizable(False, False)

root.title("Graph")
root["bg"] = bg_color

main_menu = tkinter.Menu(bg=input_bg_color)
root.config(menu=main_menu)
menu = tkinter.Menu(main_menu)
menu.add_command(label='Error keys', command=error_keys)
main_menu.add_cascade(label='Info', menu=menu)

head_frame = tkinter.Frame(bg=bg_color)
warning_label = tkinter.Label(master=head_frame, text="", bg=bg_color, fg="red", font='Calibri 18')

create_input_field(head_frame, "F(x): ", None)
create_input_field(head_frame, "Start of the segment: ", n_checker("float", 1))
create_input_field(head_frame, "End of the segment: ", n_checker("float", 1))
create_input_field(head_frame, "Step: ", n_checker("float", 0))
create_input_field(head_frame, "Accuracy (eps): ", n_checker("float", 0))
create_input_field(head_frame, "Max number of iterations: ", n_checker("int", 0))

warning_label.grid(pady=10)

start_btn = tkinter.Button(head_frame, bg="green", fg=fg_color, text="Start", font='Calibri 18',
                           width=10, command=start_computing)
start_btn.grid(pady=10)
head_frame.grid(row=0, column=0, pady=30)

table = Treeview()
table.grid(row=1, column=0, columnspan=6, pady=50)
headers = ["№", "[xi; xi+1]", "x’", "f(x’)", "Iterations number", "Error key"]
table["columns"] = headers

for header in headers:
    table.heading(header, text=header, anchor='center')

tkinter.Label(text="Made by @Talkasi", bg=bg_color, fg=fg_color).grid(columnspan=6)
root.mainloop()
