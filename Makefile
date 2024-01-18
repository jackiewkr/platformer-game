CC         := clang
CFLAGS     := -Wall -Werror
DEBUGFLAGS := -g -gdwarf-4

INCLUDES   := src/main.c

LDFLAGS    := -lSDL2 -D_REENTRANT -I/usr/include/SDL2 -lSDL2_image

compile:
	${CC} -o main ${CFLAGS} ${INCLUDES} ${LDFLAGS}

compile_debug:
	${CC} -o main_D ${CFLAGS} ${DEBUGFLAGS} ${INCLUDES} ${LDFLAGS}
