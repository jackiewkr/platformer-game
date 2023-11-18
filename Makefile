CC = clang
CFLAGS = -Wall -Werror
INCLUDES = src/level/level.c src/system/graphics/window.c \
src/system/graphics/draw_routines.c src/system/graphics/imgtex.c \
src/system/events/error-handler.c src/system/events/events.c \
src/system/structures/queue.c src/system/structures/text.c 

LDFLAGS = -lSDL2 -D_REENTRANT -I/usr/include/SDL2 -I/usr/include/json-c -ljson-c -lSDL2_image -g -gdwarf-4

compile:
	${CC} -o build/main src/main.c ${CFLAGS} ${INCLUDES} ${LDFLAGS}

compile_lvl:
	${CC} -o build/level-designer src/level-designer.c ${CFLAGS} ${INCLUDES} ${LDFLAGS}

