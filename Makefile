CC = clang
CFLAGS = -Wall -Werror
INCLUDES = libs/sdl_wrapper/window.c libs/sdl_wrapper/draw_routines.c \
           libs/data_structures/queue.c libs/error-handler/error-handler.c \
           libs/sdl_wrapper/imgtex.c libs/tilemap.c libs/events.c

LDFLAGS = -lSDL2 -D_REENTRANT -I/usr/include/SDL2 -I/usr/include/json-c -ljson-c -lSDL2_image -g -gdwarf-4

build:
	${CC} -o main main.c ${CFLAGS} ${INCLUDES} ${LDFLAGS}

build_level:
	${CC} -o level-designer level-designer.c ${CFLAGS} ${INCLUDES} ${LDFLAGS}

