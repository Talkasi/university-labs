import tkinter
from tkinter import *
from logic import *

answer_label = 0


def input_number_field(master, number):
    tkinter.Label(master=master, text="Enter {} number:".format(number), font=('Calibri 18')).grid(column=0, row=0)
    reg = root.register(input_check)
    field_entry = tkinter.Entry(master=master, validate="key", validatecommand=(reg, "%P"))
    field_entry.grid(column=0, row=1)
    tkinter.Button(master=master, text="Clean", command=lambda field=field_entry: clean([field])).grid(column=1, row=1)

    # Input buttons
    in_btn_frame = tkinter.Frame(master=master)
    tkinter.Button(master=in_btn_frame, text="+", command=lambda char="+": put(field_entry, char)).grid(column=0, row=0)
    tkinter.Button(master=in_btn_frame, text="-", command=lambda char="-": put(field_entry, char)).grid(column=1, row=0)
    tkinter.Button(master=in_btn_frame, text="1", command=lambda char="1": put(field_entry, char)).grid(column=2, row=0)
    tkinter.Button(master=in_btn_frame, text="0", command=lambda char="0": put(field_entry, char)).grid(column=3, row=0)
    tkinter.Button(master=in_btn_frame, text=".", command=lambda char=".": put(field_entry, char)).grid(column=4, row=0)

    in_btn_frame.grid(column=0, row=2)

    return field_entry


def operator_field(master, entry1, entry2, answer_label):
    operator_frame = tkinter.Frame(master=master)
    tkinter.Label(master=operator_frame, text="Choose operator to\nget an answer:",
                  font=('Calibri 18')).grid(column=0, row=0)

    operator_buttons_frame = tkinter.Frame(master=operator_frame)
    tkinter.Button(master=operator_buttons_frame, text="+",
                   command=lambda a=entry1, b=entry2, char="+", ans=answer_label: compute(a, b, char, ans)).grid(
        column=0, row=0)
    tkinter.Button(master=operator_buttons_frame, text="-",
                   command=lambda a=entry1, b=entry2, char="-", ans=answer_label: compute(a, b, char, ans)).grid(
        column=1, row=0)
    tkinter.Button(master=operator_buttons_frame, text="*",
                   command=lambda a=entry1, b=entry2, char="*", ans=answer_label: compute(a, b, char, ans)).grid(
        column=2, row=0)
    operator_buttons_frame.grid(column=0, row=1, pady=10)
    operator_frame.grid(pady=30)

    tkinter.Button(master=master, text="Clean all",
                   command=lambda e1=entry1, e2=entry2: clean([e1, e2])).grid(column=0, row=2, pady=10)


def main_menu():
    # Name block
    pack_frame = tkinter.Frame()
    name_frame = tkinter.Frame(pack_frame)
    tkinter.Label(master=name_frame, text="Binary calculator", font=('Calibri 30')).grid(column=0, row=0)
    tkinter.Label(master=name_frame, text="Sum, sub & mul binary numbers!", font=('Calibri 20')).grid(column=0, row=1)
    name_frame.pack(side="top", pady=10)

    # Body block
    body_frame = tkinter.Frame(pack_frame)

    body_frame1 = tkinter.Frame(master=body_frame)

    number1_frame = tkinter.Frame(master=body_frame1)
    entry1 = input_number_field(number1_frame, "first")
    number2_frame = tkinter.Frame(master=body_frame1)
    entry2 = input_number_field(number2_frame, "second")
    number1_frame.grid(column=0, row=0, pady=5)
    number2_frame.grid(column=0, row=1, pady=5)

    body_frame2 = tkinter.Frame(master=body_frame)

    global answer_label
    answer_label = tkinter.Label(pack_frame, text="", font=('Calibri 15'))

    operator_frame = tkinter.Frame(master=body_frame2)
    operator_field(operator_frame, entry1, entry2, answer_label)
    operator_frame.grid(column=0, row=1)

    body_frame1.grid(column=0, row=0, padx=20)
    body_frame2.grid(column=1, row=0, padx=20)

    body_frame.pack(pady=15)
    answer_label.pack(pady=10)

    # Footer block
    tkinter.Label(pack_frame, text="Made by @Talkasi", font=('Calibri 12')).pack(pady=10, side="bottom")
    pack_frame.pack(fill=BOTH, expand=True)
    return 0


def input_check(text):
    bo = False
    if set("01.+-").issuperset(set(text)) and text.count('.') <= 1 and (
            text.count('+') + text.count('-') == 1 and text[0] in '+-' or
            text.count('+') + text.count('-') == 0):
        answer_label.config(text="", fg="green")
        bo = True
    else:
        answer_label.config(text="Wrong input...", fg="red", font="14")
    return bo


def clean(field):
    for el in field:
        el.delete(0, END)


def put(field, char):
    field.insert(END, char)


def compute(a, b, char, answer_label):
    first_arg = a.get()
    second_arg = b.get()
    first_com = "+"
    second_com = "+"

    if first_arg[0] in "+-":
        first_com = first_arg[0]
        first_arg = first_arg[1:]

    if second_arg[0] in "+-":
        second_com = second_arg[0]
        second_arg = second_arg[1:]

    first_arg, second_arg = equal_form_converter(first_arg, second_arg)

    ans = ""
    if char == "*":
        ans = mul(first_arg, second_arg)
        if first_com + second_com in ["+-", "-+"]:
            ans = "-" + ans
    elif first_com + second_com + char in ["+++", "+--"]:
        ans = sum_(first_arg, second_arg)
    elif first_com + second_com + char in ["--+", "-+-"]:
        ans = "-" + sub_(first_arg, second_arg)
    elif first_com + second_com + char in ["+-+", "++-"]:
        if float(first_arg) >= float(second_arg):
            ans = sub_(first_arg, second_arg)
        else:
            ans = "-" + sub_(second_arg, first_arg)
    elif first_com + second_com + char in ["---", "-++"]:
        if float(second_arg) >= float(first_arg):
            ans = sub_(second_arg, first_arg)
        else:
            ans = "-" + sub_(first_arg, second_arg)

    if ans[-1] == ".":
        ans += "0"

    if ans[0] == ".":
        ans = "0" + ans
    answer_label.config(text="Answer: " + ans)
    return 0


if __name__ == "__main__":
    root = Tk()
    root.geometry("640x480")
    root.resizable(False, False)

    main_menu()

    root.mainloop()
