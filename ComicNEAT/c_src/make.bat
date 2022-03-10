gcc -Wall -O2 -shared -fPIC -o ../comic_windows.dll comic.c -lmingw32 -lSDL2main -lSDL2
gcc -Wall -O0 -g -o ../comic.exe comic.c -lmingw32 -lSDL2main -lSDL2
