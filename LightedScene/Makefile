#---------------------------------------------------------------------
# Builds the Lighted Scene program
# Includes Eck's camera API
#---------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -c
LDFLAGS = -lglut -lGL -lGLU

OBJS = scene.o camera.o shapes.o

a.out: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o a.out

scene.o: scene.cpp
	$(CC) $(CFLAGS) scene.cpp

camera.o: camera.cpp camera.h
	$(CC) $(CFLAGS) camera.cpp

shapes.o: shapes.cpp shapes.hpp
	$(CC) $(CFLAGS) shapes.cpp

clean:
	rm -f a.out $(OBJS)
