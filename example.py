from ctypes import CDLL
import sys
lib_path = './comic_linux.so'
try:
    my_function_lib = CDLL(lib_path)
except:
    print("erreur")

my_fun = my_function_lib.main
my_fun()
print("done")
