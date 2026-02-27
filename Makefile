PROJ = game
FLAGS = $(shell sdl2-config --cflags) -g
LIBS = $(shell sdl2-config --libs)

run: ${PROJ}.exe
	./$<

${PROJ}.exe: ${PROJ}.cpp
	g++ ${FLAGS} $< -o $@ ${LIBS}

clean:
	rm ${PROJ}.exe