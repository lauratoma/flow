PLATFORM = $(shell uname)

PROGRAMS = flow

DEFAULT: $(PROGRAMS)

#### EXPERIMENTS MODE 
#### using -DNDEBUG turns asserts off. Use it only for timing. 
##CFLAGS = -m64 -Winline -DNDEBUG -O3 -Wall 

#DEBUG MODE 
CFLAGS = -m64 -Winline -g -O3 -Wall

CC = g++ $(CFLAGS)

flow:  main.o drainage.o map.o  grid.o pixel_buffer.o
	$(CC) -o $@ main.o drainage.o map.o  grid.o pixel_buffer.o $(LIBS)

main.o: main.c drainage.hpp map.h  grid.h  pixel_buffer.h stb_image_write.h
	$(CC) $(CFLAGS) -o $@ -c main.c 

drainage.o: drainage.cpp drainage.hpp grid.h 
	$(CC) $(CFLAGS) -o $@ -c drainage.cpp

map.o: map.c map.h grid.h pixel_buffer.h stb_image_write.h
	$(CC) $(CFLAGS) -o $@ -c map.c

grid.o: grid.c grid.h
	$(CC) $(CFLAGS) -o $@ -c grid.c

pixel_buffer.o: pixel_buffer.c pixel_buffer.h stb_image_write.h
	$(CC) $(CFLAGS) -o $@ -c pixel_buffer.c

clean: 
	rm -f *.o $(PROGRAMS)
