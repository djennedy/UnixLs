CFLAGS = -Wall -Werror -g

all: build

build:
	gcc $(CFLAGS) main.c cleanup.c  dirContent.c getDirContent.c printDirContent.c translateToString.c printRecursively.c -o UnixLs
	
clean:
	rm -f UnixLs