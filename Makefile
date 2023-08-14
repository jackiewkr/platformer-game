CC = clang
CFLAGS = -Wall
INCLUDES = main.c libs/tilemap.c libs/state.c libs/point.c libs/physics.c libs/events.c libs/actor.c libs/draw/draw.c libs/draw/draw_tilemap.c libs/draw/draw_text.c libs/draw/draw_actor.c libs/collision.c

LDFLAGS = -lallegro -lallegro_image -lallegro_primitives

build:
	${CC} -o main ${CFLAGS} ${INCLUDES} ${LDFLAGS}

