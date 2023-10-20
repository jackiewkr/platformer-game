#ifndef VECTORS_H_
#define VECTORS_H_
/**
 * vectors.h
 * =========
 * Defines vectors for 2D and 3D data types.
 *
 * By JacquelineW.
 **/

typedef struct Float2D {
	float x;
	float y;
} f_vec2_t;

typedef struct Float3D {
	float x;
	float y;
	float z;
} f_vec3_t;

typedef struct UInt2D {
	unsigned int x;
	unsigned int y;
} ui_vec2_t;

typedef struct UInt3D {
	unsigned int x;
	unsigned int y;
	unsigned int z;
} ui_vec3_t;

#endif //VECTORS_H_
