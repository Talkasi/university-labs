import tkinter as tk
from tkinter import messagebox

POINT_SIZE = 2
CANVAS_WIDTH = 500
CANVAS_HEIGHT = 500
points = []
circles = []
lighted_circle = None


def create_point(x, y):
    return canvas.create_oval(x - POINT_SIZE, y - POINT_SIZE,
                              x + POINT_SIZE, y + POINT_SIZE,
                              fill="orange", outline='')


def create_circle(x, y, r):
    return canvas.create_oval(x - r, y - r,
                              x + r, y + r)


def get_and_check_value_by_canvas(f_ent, name):
    try:
        f = float(f_ent.get())
    except:
        error_message(f"Error: {name} entry is empty.")
        return None

    if f > CANVAS_WIDTH or f > CANVAS_HEIGHT or f < 0:
        error_message(f"Error: {name} out of canvas.")
        return None

    return f


def create_fig(figure_flag, x_ent, y_ent, r_ent):
    x = get_and_check_value_by_canvas(x_ent, "x")
    y = get_and_check_value_by_canvas(y_ent, "y")
    if x is None or y is None:
        return

    if figure_flag == 0:  # point
        create_point(x, y)
        points.append([x, y])
        return

    if figure_flag == 1:  # circle
        r = get_and_check_value_by_canvas(r_ent, "r")
        if r is None:
            return

        create_circle(x, y, r)
        circles.append([x, y, r])
        return


def light_special_circle():
    if len(circles) == 0:
        error_message("Error: no circles found.")
        return

    min_circle_i = 0
    min_dif = CANVAS_WIDTH * CANVAS_HEIGHT

    for i in range(len(circles)):
        in_circle = 0
        out_of_circle = 0
        for p in points:
            if (p[0] - circles[i][0]) ** 2 + (p[1] - circles[i][1]) ** 2 < circles[i][2] ** 2:
                in_circle += 1
            else:
                out_of_circle += 1

        if abs(in_circle - out_of_circle) < min_dif:
            min_circle_i = i
            min_dif = abs(in_circle - out_of_circle)

    global lighted_circle
    if lighted_circle is not None:
        canvas.delete(lighted_circle)

    lighted_circle = canvas.create_oval(circles[min_circle_i][0] - circles[min_circle_i][2],
                                        circles[min_circle_i][1] - circles[min_circle_i][2],
                                        circles[min_circle_i][0] + circles[min_circle_i][2],
                                        circles[min_circle_i][1] + circles[min_circle_i][2],
                                        outline="green", width=6)


def n_checker(_type):
    def checker(text):
        len_text = len(text)
        if len_text == 0:
            return True

        if len_text == 1 and text[0] in "+-":
            return True

        if _type == "float":
            try:
                float(text)
            except:
                error_message("Error: wrong input.")
                return False
        else:
            try:
                int(text)
            except:
                error_message("Error: wrong input.")
                return False

        return True

    return checker


def clear_canvas():
    global points
    global circles

    points = []
    circles = []
    canvas.delete('all')


def info():
    text = 'Find such a circle, the difference between the number of points inside and outside of which is minimal.'

    messagebox.showinfo('Description', text)


def error_message(text):
    messagebox.showinfo('Error', text)


def mmove(event):
    points.append([event.x, event.y])
    create_point(event.x, event.y)


root = tk.Tk()
root.resizable(width=False, height=False)
root.title('Lab04')

main_menu = tk.Menu(root)
root.config(menu=main_menu)
menu_item = tk.Menu(main_menu)
menu_item.add_command(label='Description', command=info)
main_menu.add_cascade(label='Menu', menu=menu_item)

reg = root.register(n_checker("float"))

label_input_x = tk.Label(root, text='x:')
label_input_x.grid(row=0, column=0, padx=5, pady=5)

entry_input_x = tk.Entry(root, validate="key", validatecommand=(reg, "%P"))
entry_input_x.grid(row=0, column=1, padx=5, pady=5)

label_input_y = tk.Label(root, text='y:')
label_input_y.grid(row=1, column=0, padx=5, pady=5)

entry_input_y = tk.Entry(root, validate="key", validatecommand=(reg, "%P"))
entry_input_y.grid(row=1, column=1, padx=5, pady=5)

label_input_r = tk.Label(root, text='R:')
label_input_r.grid(row=2, column=0, padx=5, pady=5)

entry_input_r = tk.Entry(root, validate="key", validatecommand=(reg, "%P"))
entry_input_r.grid(row=2, column=1, padx=5, pady=5)

button_add_point = tk.Button(root, text="Add point",
                             command=lambda fig=0, x=entry_input_x, y=entry_input_y, r=entry_input_r:
                             create_fig(fig, x, y, r))
button_add_point.grid(row=0, column=2, stick='wens', padx=5, pady=5)

button_circle_point = tk.Button(root, text="Add circle",
                                command=lambda fig=1, x=entry_input_x, y=entry_input_y, r=entry_input_r:
                                create_fig(fig, x, y, r))
button_circle_point.grid(row=1, column=2, stick='wens', padx=5, pady=5)

button_clear_canvas = tk.Button(root, text="Clear canvas", command=clear_canvas)
button_clear_canvas.grid(row=1, column=3, stick='wens', padx=5, pady=5)

button_result = tk.Button(root, text="Process", command=light_special_circle)
button_result.grid(row=0, column=3, rowspan=1, stick='wens', padx=5, pady=5)

label_root = tk.Label(root, text='Made by @Talkasi', fg="dark grey")
label_root.grid(row=2, column=2, columnspan=2, padx=5, pady=5)

canvas = tk.Canvas(root, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, bg="white")
canvas.grid(row=3, column=0, columnspan=4, stick='wens', padx=5, pady=5)

canvas.bind('<Button>', mmove)
root.mainloop()
