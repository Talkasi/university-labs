import tkinter
import logic
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from math import *

bg_color = "dark green"
fg_color = "white"


def start(func_e, st_e, end_e, error_l, answer_l):
    def strt():
        error_label.config(text="")
        func = func_e.get()

        st = st_e.get()
        try:
            st = float(st)
        except:
            error_l.config(text="Wrong start")
            return

        end = end_e.get()
        try:
            end = float(end)
        except:
            error_l.config(text="Wrong end")
            return

        if st >= end:
            error_l.config(text="Wrong end")
            return

        try:
            error_label.config(text="")
            ans = logic.clarification(func, st, end)
            if st <= ans <= end:
                ans = str(ans)
            else:
                ans = "error in finding."
            answer_l.config(text="Answer: " + ans)
        except:
            error_l.config(text="Wrong function")
            return

        plt(func, st, end)

    return strt


def plt(func, a, b):
    fig = Figure(figsize=(4, 2))
    graph = fig.add_subplot()

    x = np.linspace(a, b)
    y = np.array([logic.f(x_i, func) for x_i in x])

    graph.plot(x, y)
    graph.grid()

    graph.set_ylabel("f(x) =" + func)
    graph.set_xlabel("x")

    canvas = FigureCanvasTkAgg(fig)
    canvas.draw()
    canvas.get_tk_widget().grid(column=0, row=3, pady=10, columnspan=2)


root = tkinter.Tk()
main_frame = tkinter.Frame(bg=bg_color)

func_label = tkinter.Label(master=main_frame, text="Function: ", bg=bg_color, fg=fg_color)
func_label.grid(column=0, row=0, pady=10)
func_entry = tkinter.Entry(master=main_frame)
func_entry.grid(column=1, row=0, pady=10)

start_label = tkinter.Label(master=main_frame, text="X start: ", bg=bg_color, fg=fg_color)
start_label.grid(column=0, row=1, pady=10)
start_entry = tkinter.Entry(master=main_frame)
start_entry.grid(column=1, row=1, pady=10)

end_label = tkinter.Label(master=main_frame, text="X end: ", bg=bg_color, fg=fg_color)
end_label.grid(column=0, row=2, pady=10)
end_entry = tkinter.Entry(master=main_frame)
end_entry.grid(column=1, row=2, pady=10)

error_label = tkinter.Label(master=main_frame, fg="dark red", bg=bg_color)
error_label.grid(columnspan=2)

answer_label = tkinter.Label(master=main_frame, fg=fg_color, font="18", bg=bg_color)
answer_label.grid(columnspan=2, row=5)

start_btn = tkinter.Button(master=main_frame, text="Start", width=40, fg=bg_color,
                           command=start(func_entry, start_entry, end_entry, error_label, answer_label))
start_btn.grid(columnspan=2)
main_frame.grid()

root.mainloop()
