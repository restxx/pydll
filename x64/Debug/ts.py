# coding=utf-8

import pydll
import struct
from ctypes import byref, c_char, cast, c_char_p, pointer, addressof, POINTER, c_ubyte, string_at, c_byte

player = pydll.Player(178,24)

print("Yout age =%d"%player.GetAge())

print("Yout height =%d"%player.GetHeight())

print("i will set your age and height")

player.SetHeight(170)

player.SetAge(15)

print("Yout age =%d"%player.GetAge())

print("Yout height =%d"%player.GetHeight())


buf = struct.pack('20B', 0x41, 0x42, 0x43, 0xFF, 0x90, 0x41, 0x42, 0x43, 0x44, 0x90, 0x41, 0x42, 0x43, 0x44, 0x90, 0x41, 0x42, 0x43, 0x44, 0x90)
a = list(buf)
player.SetItem(a)
print(a)

print(pydll.MyEnum.TS0)

# p = (c_byte * 5)()
# for idx, i in enumerate(buf):
#     p[idx] = i
# m = cast(p, c_char_p)
#
#
# player.Process(m, len(buf))
# https://docs.python.org/3.6/library/ctypes.html