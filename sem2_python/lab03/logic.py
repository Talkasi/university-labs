from PIL import Image


def encode(img_field, message_field, warning_label):
    img_path = img_field.get()

    try:
        image = Image.open(img_path).convert('RGB')
    except:
        warning_label.config(fg="red", text="Wrong path...")
        return

    img_size = image.size

    message = message_field.get("1.0", 'end') + '\0'
    message_bits = string_to_bits(message)

    m_i = 0
    flag_end = 0
    m_len = len(message_bits)
    for y in range(img_size[1]):
        for x in range(img_size[0]):
            r, g, b = image.getpixel((x, y))
            pix = [r, g, b]

            for i in range(3):
                if m_i < m_len:
                    if message_bits[m_i] != bin(pix[i])[-1] and bin(pix[i])[-1] == '1':
                        pix[i] = pix[i] - 1
                    elif message_bits[m_i] != bin(pix[i])[-1]:
                        pix[i] = pix[i] + 1

                    m_i += 1
                else:
                    flag_end = 1
                    break

            image.putpixel((x, y), tuple(pix))
            if flag_end:
                break
        if flag_end:
            break

    new_img_path = img_path.split('/')
    new_img_path = '/'.join(new_img_path[:-2] + ['new_' + new_img_path[-1]])

    if new_img_path[-4:] != ".png":
        new_img_path += ".png"

    image.save(new_img_path, "PNG")


def string_to_bits(string):
    string_bits = []
    for char in string:
        bin_r = bin(ord(char))[2:].zfill(8)
        for bit in bin_r:
            string_bits.append(bit)

    return string_bits


def decode(img_field, message_field, warning_label):
    img_path = img_field.get()

    try:
        image = Image.open(img_path)
    except:
        warning_label.config(fg="red", text="Wrong path...")
        return

    img_size = image.size

    message_bits = ''
    message = ""

    flag_end = 0
    for y in range(img_size[1]):
        for x in range(img_size[0]):
            r, g, b = image.getpixel((x, y))
            pix = [r, g, b]

            for i in range(3):
                message_bits += bin(pix[i])[-1]
                if len(message_bits) == 8:
                    if chr(int(message_bits, 2)) == '\0':
                        flag_end = 1
                        break
                    message += chr(int(message_bits, 2))
                    message_bits = ''

            if flag_end:
                break
        if flag_end:
            break

    message_field.delete("1.0", "end")
    message_field.insert("1.0", message)
