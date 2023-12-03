# Program to find out duration of the video (mp4 format)

import struct

file = open("a.mp4", "rb")
type_a = ""
size_a = 0

while type_a != "moov":
    size_a = struct.unpack(">I", file.read(4))[0]
    type_a = struct.unpack("4s", file.read(4))[0].decode("ascii")
    file.seek(size_a - 8, 1)

file.seek(-size_a + 28, 1)

time_scale = struct.unpack(">I", file.read(4))[0]
duration = struct.unpack(">I", file.read(4))[0]

print("Duration of the video is {:.7g} seconds.".format(duration / time_scale))
