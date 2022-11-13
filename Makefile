build: sdl-hello-world temporary

run: run-sdl-hello-world

run-sdl-hello-world: sdl-hello-world
	./sdl-hello-world

sdl-hello-world: sdl-hello-world.cpp
	g++ $< -o $@ -lSDL2

run-temporary: temporary
	./temporary

temporary: temporary.cpp
	g++ $< -o $@ -lSDL2

all: ende in-out

ende: ende.c
	gcc ende.c -o ende

in-out: in-out.c
	gcc in-out.c -o in-out

