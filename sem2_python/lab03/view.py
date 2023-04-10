from PIL import Image, ImageTk
import tkinter
import logic

# bg_color1 = "#4CAF50"
# bg_color2 = "white"
bg_color1 = "gray32"
bg_color2 = "white"


def create_title():
    title_frame = tkinter.Frame(bg=bg_color1)
    tkinter.Label(master=title_frame, text="Send secret message to your friend!", font="Calibri 25", bg=bg_color1,
                  fg=bg_color2).pack(pady=18)
    title_frame.pack(fill="x")


def create_text(main_f):
    text_frame = tkinter.Frame(master=main_f, bg=bg_color2)
    tkinter.Label(master=text_frame, text="Text to encode/Decoded text:", font="Calibri 18", bg=bg_color2,
                  fg=bg_color1).grid(row=0, column=0, pady=15, sticky='W')

    text = tkinter.Text(master=text_frame, bg=bg_color1, width=40)
    text.grid(row=1, column=0)
    text_frame.grid(row=1, column=0, pady=10, padx=30)

    return text


def get_image_field(img_f, load_img, warning_l, img_label, message_f):
    get_field = tkinter.Frame(master=img_f, bg=bg_color2)
    tkinter.Label(master=get_field, bg=bg_color2, fg=bg_color1, text="Path to an image: ",
                  font="Calibri 18").grid(row=0, column=0, sticky='W')

    img_entry = tkinter.Entry(master=get_field, bg=bg_color2, font="Calibri")
    img_entry.grid(row=1, column=0, pady=10, sticky='W')

    load_btn = tkinter.Button(master=get_field, bg=bg_color1, fg=bg_color2, text="Load image", font="Calibri 15",
                              command=load_img(img_entry, warning_l, img_label))
    load_btn.grid(row=1, column=1, pady=10, sticky='W')

    encode_btn = tkinter.Button(master=get_field, bg=bg_color1, fg=bg_color2, text="Encode", font="Calibri 15",
                                command=lambda img=img_entry, msg=message_f: logic.encode(img, msg, warning_l))
    encode_btn.grid(row=1, column=2, pady=10, padx=42, sticky='W')

    decode_btn = tkinter.Button(master=get_field, bg=bg_color1, fg=bg_color2, text="Decode", font="Calibri 15",
                                command=lambda img=img_entry, msg=message_f: logic.decode(img, msg, warning_l))
    decode_btn.grid(row=1, column=3, pady=10, sticky='W')

    get_field.grid(row=0, column=0, sticky='W')


def create_footer():
    footer_frame = tkinter.Frame(bg=bg_color1)
    tkinter.Label(master=footer_frame, bg=bg_color1, fg=bg_color2, font="Calibri 14",
                  text="Made by @Talkasi").pack(pady=10)
    footer_frame.pack(side='bottom', fill="x")


def load_image(path_entry, warning_l, image_label):
    def load():
        path = path_entry.get()

        warning_l.config(fg=bg_color1, text="Try and enjoy!")
        try:
            img = ImageTk.PhotoImage(Image.open(path).convert('RGB').resize((650, 440)))
        except:
            warning_l.config(fg="red", text="Wrong path...")
            return

        image_label.config(image=img)
        image_label.image = img

    return load


root = tkinter.Tk()
root.geometry('1400x830')
root.resizable(False, False)

root.title("Secret image converter")
root["bg"] = bg_color2

create_title()

main_frame = tkinter.Frame(bg=bg_color2)

text_field = create_text(main_frame)

img_frame = tkinter.Frame(master=main_frame, bg=bg_color2)

warning_label = tkinter.Label(master=img_frame, bg=bg_color2, fg=bg_color1, font="Calibri 18", text="Try and enjoy!")
warning_label.grid(row=2, column=0, pady=2)

img = ImageTk.PhotoImage(Image.open("cat.png").resize((650, 440)))
label = tkinter.Label(img_frame, bg=bg_color2, image=img)
get_image_field(img_frame, load_image, warning_label, label, text_field)
label.grid(row=1, column=0, pady=10)

img_frame.grid(row=1, column=1, pady=10, padx=30)
main_frame.pack(pady=20)

create_footer()

root.mainloop()
