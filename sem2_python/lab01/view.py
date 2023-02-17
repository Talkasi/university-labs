import tkinter
from tkinter import *
from logic import *


def input_nuber_field(master):
    tkinter.Label(master=master, text="Enter first number:", font=('Calibri 18')).grid(column=0, row=0)
    tkinter.Entry(master=master).grid(column=0, row=1)
    tkinter.Button(master=master, text="Clean", command=clean).grid(column=1, row=1)

    # Input buttons
    input_buttons_frame = tkinter.Frame(master=master)
    tkinter.Button(master=input_buttons_frame, text="+", command=put).grid(column=0, row=0)
    tkinter.Button(master=input_buttons_frame, text="-", command=put).grid(column=1, row=0)
    tkinter.Button(master=input_buttons_frame, text="1", command=put).grid(column=2, row=0)
    tkinter.Button(master=input_buttons_frame, text="0", command=put).grid(column=3, row=0)
    tkinter.Button(master=input_buttons_frame, text=".", command=put).grid(column=4, row=0)
    input_buttons_frame.grid(column=0, row=2)

    return 0


def operator_field(master):
    tkinter.Label(master=master, text="Choose operator to\nget an answer:", font=('Calibri 18')).grid(column=0, row=0)

    operator_buttons_frame = tkinter.Frame(master=master)
    tkinter.Button(master=operator_buttons_frame, text="+", command=sum_).grid(column=0, row=0)
    tkinter.Button(master=operator_buttons_frame, text="-", command=sub_).grid(column=1, row=0)
    tkinter.Button(master=operator_buttons_frame, text="*", command=mul).grid(column=2, row=0)
    operator_buttons_frame.grid(column=0, row=1, pady=10)

    answer_frame = tkinter.Frame(master=master)
    tkinter.Label(master=answer_frame, text="The answer is:", font=('Calibri 18')).grid(column=0, row=0)
    tkinter.Label(master=answer_frame, text="Answer", font=('Calibri 18')).grid(column=0, row=1)
    answer_frame.grid(column=0, row=2, pady=15)

    tkinter.Button(master=master, text="Clear all", command=clean).grid(column=0, row=4)


def main_menu():
    # Name block
    grid_packing_name = tkinter.Frame()
    name_frame = tkinter.Frame(grid_packing_name)
    tkinter.Label(master=name_frame, text="Binary calculator", font=('Calibri 30')).grid(column=0, row=0)
    tkinter.Label(master=name_frame, text="Sum, sub & mul binary numbers!", font=('Calibri 20')).grid(column=0, row=1)
    name_frame.pack(side="top", pady=10)
    grid_packing_name.grid(column=0, row=0)

    # Body block
    grid_packing_body = tkinter.Frame()
    body_frame = tkinter.Frame(grid_packing_body)

    body_frame1 = tkinter.Frame(master=body_frame)

    number1_frame = tkinter.Frame(master=body_frame1)
    input_nuber_field(number1_frame)
    number2_frame = tkinter.Frame(master=body_frame1)
    input_nuber_field(number2_frame)
    number1_frame.grid(column=0, row=0, pady=5)
    number2_frame.grid(column=0, row=1, pady=5)

    body_frame2 = tkinter.Frame(master=body_frame)

    operator_frame = tkinter.Frame(master=body_frame2)
    operator_field(operator_frame)
    operator_frame.grid(column=0, row=1)

    body_frame1.grid(column=0, row=0, padx=20)
    body_frame2.grid(column=1, row=0, padx=20)

    body_frame.pack(pady=15)
    grid_packing_body.grid(column=0, row=1)

    # Footer block
    grid_packing_footer = tkinter.Frame()
    tkinter.Label(grid_packing_footer, text="Made by @Talkasi", font=('Calibri 12')).pack(pady=10, side="bottom")
    grid_packing_footer.grid(column=0, row=2)
    return 0


def clean():
    entry1.delete(0, END)


def put():
    entry1.insert(c)


if __name__ == "__main__":
    root = Tk()
    root.geometry("640x480")
    root.columnconfigure(0, weight=1, minsize=250)
    root.rowconfigure([0, 1, 2], weight=1, minsize=100)

    main_menu()

    root.mainloop()
