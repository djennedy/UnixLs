CFLAGS = -Wall -Werror -g

all: build

build:
	gcc $(CFLAGS) main.c cleanup.c  dirContent.c getDirContent.c printDirContent.c translateToString.c -o UnixLs -lbsd
	
clean:
	rm -f UnixLs