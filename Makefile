# makefile para Canvas. version 0.1
# uso de variables; reglas predefinidas

CC = g++
# OBJECTS = coreLoop.o carreterometro.o
TARGETS = canvas.cpp common/loadShaders.cpp common/car.cpp common/caravan.cpp common/matrix.cpp common/scene.cpp common/spot.cpp common/renderable.cpp common/ground.cpp common/object.cpp
LIBS = -lGL -lGLEW -lglut -lSOIL
CFLAGS = -g -I include


.PHONY : all
all :
	$(CC) $(TARGETS) $(LIBS) $(CFLAGS) -o aaa
