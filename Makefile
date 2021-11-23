comic: comic.c
	gcc -Wall -o comic comic.c -lSDL2

clean:
	rm comic

run: comic
	./comic
