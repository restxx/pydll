# coding=utf-8

import pydll
import struct
# from ctypes import byref, c_char, cast, c_char_p, pointer, addressof, POINTER, c_ubyte, string_at, c_byte

my = pydll.MyStruct()
print(my.x, my.para)


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
print("after", a)

player.SetDict({"test": 110})


a= int.from_bytes([0,0,0,0xF0], "little", signed=False)
player.SetUint(a)

print(pydll.MyEnum.TS0)

# player.Process(m, len(buf))
# https://docs.python.org/3.6/library/ctypes.html