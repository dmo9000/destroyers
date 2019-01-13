#ifndef __VECTOR_3__
#define __VECTOR_3__

typedef struct _vector3 {
    union {
        uint32_t x;
        uint32_t r;
    };
    union {
        uint32_t y;
        uint32_t g;
    };
    union {
        uint32_t z;
        uint32_t b;
    };
} Vector3;

#endif /* __VECTOR_3__ */


