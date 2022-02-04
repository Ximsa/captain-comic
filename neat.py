import sys
import select
from comic.comic import * 

foo = Comic()

for i in range(60):
    foo.tick(1,0,0,0,1,0)

for i in range(20):
    for j in range(2):
        foo.tick(0,0,0,0,1,0)
    for j in range(5):
        foo.tick(1,0,0,0,1,0)

    
