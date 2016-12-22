# makefile para Canvas. version 0.1
# uso de variables; reglas predefinidas

CC = g++
# OBJECTS = coreLoop.o carreterometro.o
TARGETS = canvas.cpp common/loadShaders.cpp common/triangle.cpp common/car.cpp common/matrix.cpp
LIBS = -lGL -lGLEW -lglut
CFLAGS = -g -I include


.PHONY : all
all :
	$(CC) $(TARGETS) $(LIBS) $(CFLAGS) -o aaa
