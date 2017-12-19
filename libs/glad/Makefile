CC = gcc
AR = ar rcs
CFLAGS = -O3 -c

src/libglad.a: src/glad.o
	$(AR) src/libglad.a src/glad.o

src/glad.o: src/glad.c
	$(CC) $(CFLAGS) -I include src/glad.c -o src/glad.o
