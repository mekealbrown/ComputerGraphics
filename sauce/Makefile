#---------------------------------------------------------------------
#-- Developer -- Mekeal Brown
#-- Course ----- CS3233
#-- Project ---- Homework #4: Lighted Scene
#-- Due Date --- October 23, 2024
#--
#-- Makefile to build the lighted scene program
#-- Creates obj directory to hold generated object files to keep the
#-- directory clean.
#---------------------------------------------------------------------

CC = g++
CFLAGS = -Wall -c
LDFLAGS = -lglut -lGL -lGLU
OBJ_DIR = obj
OBJS = $(OBJ_DIR)/saucy.o $(OBJ_DIR)/camera.o $(OBJ_DIR)/shapes.o

a.out: $(OBJS)
	$(CC)  $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/saucy.o: saucy.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) saucy.cpp -o $(OBJ_DIR)/saucy.o

$(OBJ_DIR)/camera.o: camera.cpp camera.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) camera.cpp -o $(OBJ_DIR)/camera.o

$(OBJ_DIR)/shapes.o: shapes.cpp shapes.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) shapes.cpp -o $(OBJ_DIR)/shapes.o

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f a.out $(OBJS)
	rmdir $(OBJ_DIR)
