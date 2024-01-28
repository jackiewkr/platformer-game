CC         := clang
CFLAGS     := -Wall -Werror
DEBUGFLAGS := -g -gdwarf-4
override TESTFLAGS  += src/tests/unity/unity.c
INCLUDES   := src/window/*.c

LDFLAGS    := -lSDL2 -D_REENTRANT -I/usr/include/SDL2 -lSDL2_image

compile:
	${CC} -o bin/game src/main.c ${CFLAGS} ${INCLUDES} ${LDFLAGS}

compile_debug:
	${CC} -o bin/gameDebug src/main.c ${CFLAGS} ${DEBUGFLAGS} ${INCLUDES} ${LDFLAGS}

compile_test:
	${CC} -o bin/tests src/tests/test.c ${CFLAGS} ${TESTFLAGS} ${INCLUDES} ${LDFLAGS}
