from PIL import Image, ImageDraw


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
    flag_end = False
    for y in range(img_size[1]):
        for x in range(img_size[0]):
            if m_i >= len(message_bits):
                flag_end = True
                break

            r, g, b = image.getpixel((x, y))

            r = (r & ~0x1) | message_bits[m_i]
            m_i += 1
            g = (g & ~0x1) | message_bits[m_i]
            m_i += 1
            b = (b & ~0x1) | message_bits[m_i]
            m_i += 1

            image.putpixel((x, y), (r, g, b))

        if flag_end:
            break

    new_img_path = img_path.split('/')
    new_img_path = '/'.join(new_img_path[:-2] + ['new_' + new_img_path[-1]])

    image.save(new_img_path, "PNG")


def string_to_bits(string):
    string_bits = []
    for char in string:
        bin_r = bin(ord(char))[2:].zfill(8)
        for bit in bin_r:
            string_bits.append(int(bit))

    while len(string_bits) % 3 != 0:
        string_bits.append(0)

    return string_bits


def decode(img_field, message_field, warning_label):
    img_path = img_field.get()

    try:
        image = Image.open(img_path)
    except:
        warning_label.config(fg="red", text="Wrong path...")
        return

    img_size = image.size
    message_bits = ""
    message_len = 0
    message = ""

    flag_end = False
    for y in range(img_size[1]):
        for x in range(img_size[0]):
            if message != "" and message[-1] == '\0':
                flag_end = True
                break
            r, g, b = image.getpixel((x, y))

            for i in [r, g, b]:
                message_bits += str(i & 0x1)
                message_len += 1

                if message_len == 8:
                    message += chr(int(message_bits, 2))
                    message_len = 0
                    message_bits = ""

        if flag_end:
            break

    message_field.delete("1.0", "end")
    message_field.insert("1.0", message)
