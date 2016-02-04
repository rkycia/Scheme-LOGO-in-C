



CFLAGS = `guile-config compile`
LIBS = `guile-config link`


.PHONY: clean build run

build: main

clean:
	rm -f main.x main.o

run: main.x
	./main.x 

main.x: main.o
	gcc $< -o $@ $(LIBS) -lm -lglut -lGL -lpthread

main.o: main1.c
	gcc -c  $< -o $@ $(CFLAGS)
