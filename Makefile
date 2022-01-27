comic: comic.c
	gcc -Wall -O0 -o comic comic.c -lSDL2

clean:
	rm comic

run: comic
	./comic

lib: comic.c
	gcc -Wall -O0 -shared -fPIC -lSDL2 comic.c -o comic_linux.so

release: comic.c
	gcc -Wall -o comic comic.c -lSDL2 -O3
