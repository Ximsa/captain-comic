import pathlib
import shutil, os, tempfile
import numpy as np
from ctypes import c_ubyte, CDLL

class Comic:
    def __init__(self, graphics = 1, sound = 1, skip_intro = 1 ):
        ## to allow for loading the library "multiple" times, call CDLL on a copy
        os.chdir(os.path.dirname(os.path.realpath(__file__)))
        suffix = ""
        libname = "./comic_linux.so"
        if(os.name == "nt"):
            suffix = ".dll"
            libname = "./comic_windows.dll"
        fp = tempfile.NamedTemporaryFile(suffix = suffix, delete=False)
        fp.close()
        shutil.copyfile(libname, fp.name)
        self.libcomic = CDLL(fp.name)
        self.libcomic.setup(c_ubyte(graphics),
                                c_ubyte(sound),
                                c_ubyte(skip_intro))
        if(os.name != "nt"):
            os.remove(fp.name)

    def tick(self, jump=0, open_door=0, teleport=0, left=0, right=0, pause=0, fire=0):
        self.libcomic.tick(c_ubyte(jump),
                           c_ubyte(open_door),
                           c_ubyte(teleport),
                           c_ubyte(left),
                           c_ubyte(right),
                           c_ubyte(pause),
                           c_ubyte(fire))
        
    def get_environment(self):
        environment = (c_ubyte * (24*20))()
        stats = (c_ubyte * 14)()
        self.libcomic.get_environment(environment, stats)
        return environment[:], stats[:]

    def reset(self):
         self.libcomic.reset();
  

        


#comic = Comic(1,1,1)
#comic.tick()
#field, stats = comic.get_environment()
#print(np.reshape(np.array(field), (20,24)))
