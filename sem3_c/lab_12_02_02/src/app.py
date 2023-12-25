import ctypes
import tkinter 

bg_color = "gray22"
fg_color = "white"
input_bg_color = "gray32"

orange="#FFB64E"
red="#DE4A36"
green="#759253"
pink="#9875A5"
blue="#6897B9"

src_arr_label = None
dst_arr_max_label = None
dst_arr_needed_label = None

src = list()
dst_max = list()
dst_needed = list()

result_src = "There is no array now."
result_dst_max = "There is no array now."
result_dst_needed = "There is no array now."

lib = ctypes.CDLL('./lib/libarr.so')

# int init_arr_by_fib(int *arr, size_t n);
_init_arr_by_fib = lib.init_arr_by_fib
_init_arr_by_fib.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t)
_init_arr_by_fib.restype = ctypes.c_int

def create_arr_by_fib(src_len):
    src = (ctypes.c_int * src_len)()
    rc = _init_arr_by_fib(src, src_len)
    return rc, list(src)


# int init_by_first_unique(int *src, size_t src_n, int *dst, size_t dst_n, size_t *n_initialized);
_init_by_first_unique = lib.init_by_first_unique
_init_by_first_unique.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, \
                                  ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, \
                                  ctypes.POINTER(ctypes.c_size_t))
_init_by_first_unique.restype = ctypes.c_size_t

def init_by_first_unique_max_dst_size(nums):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    dst_cur_len = ctypes.c_size_t(0)
    dst_max_len = len(nums)
    dst = (ctypes.c_int * dst_max_len)()

    rc = _init_by_first_unique(src, src_len, dst, dst_max_len, dst_cur_len)
    dst = dst[:dst_cur_len.value]
    return rc, list(dst)


def init_by_first_unique_needed_dst_size(nums):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    dst_cur_len = ctypes.c_size_t(0)
    dst_max_len = ctypes.c_size_t(0)

    rc = _init_by_first_unique(src, src_len, None, dst_max_len, dst_cur_len)
    dst = list()
    if rc != 0:
        dst_max_len = ctypes.c_size_t(rc)
        dst = (ctypes.c_int * dst_max_len.value)()
        rc = _init_by_first_unique(src, src_len, dst, dst_max_len, dst_cur_len)

    dst = dst[:dst_cur_len.value]
    return rc, list(dst)


def init_fib_demo(entry, src_arr_label):
    try:
        n = int(entry.get())
        global src
        rc, src = create_arr_by_fib(n)
        src_arr_label.config(text=', '.join(str(i) for i in src) if src != list() else "There is no array now.")
    except:
        src_arr_label.config(text="Error occured.")


def init_unique_demo(entry, dst_arr_max_label, dst_arr_needed_label):
    try:
        nums = list(int(i) for i in entry.get().split())
        global dst_max
        rc, dst_max = init_by_first_unique_max_dst_size(nums)
        dst_arr_max_label.config(text=', '.join(str(i) for i in dst_max) if dst_max != list() else "There is no array now.")
    except:
        dst_arr_max_label.config(text="Error occured.")

    # try:
    nums = list(int(i) for i in entry.get().split())
    global dst_needed
    rc, dst_needed = init_by_first_unique_needed_dst_size(nums)
    dst_arr_needed_label.config(text=', '.join(str(i) for i in dst_needed) if dst_needed != list() else "There is no array now.")
    # except:
        # dst_arr_needed_label.config(text="Error occured.")


def int_input_check(_sign):
    def checker(text):
        if len(text) == 0:
            return True

        if (any(' ' == i for i in text)):
            return False

        try:
            int(text)
        except:
            return False
        if (0 < int(text) <= 15):
            return True
        else:
            return False

    return checker

def arr_input_check():
    def checker(text):
        if (len(text) == 0):
            return True
        try:
            nums = text.split()
            if (len(nums) > 20):
                return False

            for n in nums:
                if n != "+" and n != "-":
                    if -99 > int(n) or int(n) > 99:
                        return False

            return True
        except:
            return False

    return checker

def draw_label_sticky(mf, txt, fg, fs, c, r, px, py):
    l = tkinter.Label(master=mf, text=txt, font=('CourierNew ' + str(fs)), bg=bg_color, fg=fg)
    l.grid(column=c, row=r, pady=py, padx=px, sticky="w")

def draw_label_thik(mf, txt, fg, fs, c, r, px, py):
    l = tkinter.Label(master=mf, text=txt, font=('CourierNewThik ' + str(fs)), bg=bg_color, fg=fg)
    l.grid(column=c, row=r, pady=py, padx=px, sticky="w")

def lib_demo(body_frame, int_input_check, arr_input_check):
    global src_arr_label
    global dst_arr_max_label
    global dst_arr_needed_label

    # Fibonacci part
    entry_frame = tkinter.Frame(body_frame, bg=bg_color)
    input_frame = tkinter.Frame(entry_frame, bg=bg_color)
    draw_label_sticky(input_frame, "Enter number of elements in the array: ", fg_color, 10, 0, 0, 0, 0)

    entry = tkinter.Entry(master=input_frame, highlightthickness=0, bg=bg_color, fg=fg_color, width=7, justify="right")
    if int_input_check is not None:
        reg = root.register(int_input_check)
        entry.config(validate="key", validatecommand=(reg, "%P"))
    entry.grid(column=1, row=0)

    draw_label_thik(entry_frame, "Number of elements should be an integer from 1 to 15.", red, 10, 0, 1, 0, 5)

    entry_frame.grid(column=0, row=0, pady=15, sticky="w")

    result_frame = tkinter.Frame(body_frame, bg=bg_color)
    draw_label_sticky(result_frame, "Array initialized by fibonacci numbers: ", fg_color, 10, 0, 0, 0, 0)
    src_arr_label = tkinter.Label(master=result_frame, text=result_src, bg=bg_color, fg=green,  font=('CourierNewThik 12'))
    src_arr_label.grid(column=0, row=1, padx=0, pady=5, sticky="w")
    tkinter.Button(master=input_frame, highlightthickness=0, bg=blue, fg=bg_color, text="Submit", \
        command=lambda e=entry, l=src_arr_label: init_fib_demo(e, l)).grid(column=2, row=0, padx=15)
    input_frame.grid(column=0, row=0, sticky="w")
    result_frame.grid(column=0, row=1, pady=15, sticky="w")

    # Unique filter part
    arr_entry_frame = tkinter.Frame(body_frame, bg=bg_color)
    arr_input_frame = tkinter.Frame(arr_entry_frame, bg=bg_color)
    draw_label_sticky(arr_input_frame, "Enter elements for the source array, separated by space: ", fg_color, 10, 0, 0, 0, 0)

    entry = tkinter.Entry(master=arr_input_frame, highlightthickness=0, bg=bg_color, fg=fg_color, width=66, justify="left")
    if arr_input_check is not None:
        reg = root.register(arr_input_check)
        entry.config(validate="key", validatecommand=(reg, "%P"))
    entry.grid(column=0, row=1, columnspan=2, pady=15, sticky="w")

    arr_input_frame.grid(column=0, row=0)
    draw_label_thik(arr_entry_frame, "Elements must be integers greater than -100 and less than 100. Max n numbers: 20", red, 10, 0, 2, 0, 5)
    arr_entry_frame.grid(column=0, row=2, pady=15, sticky="w")

    result_frame = tkinter.Frame(body_frame, bg=bg_color)
    draw_label_sticky(result_frame, "Filtered array created using the max length strategy: ", fg_color, 10, 0, 0, 0, 5)

    dst_arr_max_label = tkinter.Label(master=result_frame, text=result_dst_max, font=('CourierNewThik 12'), bg=bg_color, fg=green)
    dst_arr_max_label.grid(column=0, row=1, pady=7, padx=0, sticky="w")

    draw_label_sticky(result_frame, "Filtered array created using the needed length strategy: ", fg_color, 10, 0, 2, 0, 5)

    dst_arr_needed_label = tkinter.Label(master=result_frame, text=result_dst_needed, font=('CourierNewThik 12'), bg=bg_color, fg=green)
    dst_arr_needed_label.grid(column=0, row=3, pady=7, padx=0, sticky="w")

    tkinter.Button(master=arr_input_frame, highlightthickness=0, bg=blue, fg=bg_color, text="Submit", \
        command=lambda e=entry: init_unique_demo(e, dst_arr_max_label, dst_arr_needed_label)).grid(column=1, row=0, padx=5)
    
    result_frame.grid(column=0, row=3, sticky="w")



def draw_app():
    pack_frame = tkinter.Frame(bg=bg_color)

    name_frame = tkinter.Frame(pack_frame, bg=bg_color)
    tkinter.Label(master=name_frame, bg=bg_color, fg=orange, text="Simple array", font=('CourierNew 18')).grid(column=0, row=0)
    tkinter.Label(master=name_frame, bg=bg_color, fg=orange, text="library demonstrator", font=('CourierNew 18')).grid(column=0, row=1)
    name_frame.pack(side="top", pady=10)

    body_frame = tkinter.Frame(pack_frame, bg=bg_color)
    lib_demo(body_frame, int_input_check(0), arr_input_check())
    body_frame.pack(pady=15)

    tkinter.Label(pack_frame, bg=bg_color, fg=pink, text="Made by @Talkasi", font=('CourierNew 12')).pack(pady=10, side="bottom")
    pack_frame.pack(fill=tkinter.BOTH, expand=True)
    return 0


if __name__ == "__main__":
    root = tkinter.Tk()
    root.geometry("840x720")
    root.resizable(False, False)
    draw_app()
    root.mainloop()
