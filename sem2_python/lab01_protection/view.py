import logic
import tkinter


def from_func(ans, entry):
    number = entry.get()
    try:
        number = int(number)
    except:
        print("Fatal error")
        exit(1)
    answer = logic.ten_four(number)
    ans.config(text="Answer: " + str(answer))
    return 0


def to_func(ans, entry):
    number = entry.get()
    try:
        number = int(number)
    except:
        print("Fatal error")
        print("Fatal error")
        exit(1)
    answer = logic.four_ten(number)
    ans.config(text="Answer: " + str(answer))
    return 0


root = tkinter.Tk()
root.geometry("640x480")
root.resizable(False, False)

tkinter.Label(master=root, text="Converter", font='Calibri 30').pack(pady=30)
entry1 = tkinter.Entry()
entry1.pack(pady=10)

answer = tkinter.Label(master=root, text="", fg="green", font='Calibri 20')

from_ = lambda ans=answer, entry=entry1: from_func(ans, entry)
tkinter.Button(master=root, text="Convert from 10 to 4", font='Calibri 20', command=from_).pack(pady=8)
to_ = lambda ans=answer, entry=entry1: to_func(ans, entry)
tkinter.Button(master=root, text="Convert to 10 from 4", font='Calibri 20', command=to_).pack(pady=8)

answer.pack(pady=50)

root.mainloop()
