CFLAGS = -Wall -Werror 

all: build

build:
	gcc $(CFLAGS) cleanup.c dirContent.c getDirContent.c main.c printDirContent.c translateToString.c 
	
clean:
	rm UnixLs