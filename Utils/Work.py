import os

ircontent = list(os.scandir("C:/OpenCV/4.6.0/build/x64/vc17/lib/Debug"))

for value in ircontent:
    if ".lib" in (value.name):
        print(value.name)