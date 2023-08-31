CC = clang
CFLAGS = -Wall -Werror
INCLUDES = main.c libs/glfw_wrapper/window.c libs/error-handler/error-handler.c

LDFLAGS = -lglfw

build:
	${CC} -o main ${CFLAGS} ${INCLUDES} ${LDFLAGS}

