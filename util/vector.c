#ifndef VECTOR_C_
#define VECTOR_C_

#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

/* A C++ vector like container implementation */

static const uint32_t INIT_CAP  = 16;
static const uint32_t SCALE     = 2;

static void _vector_grow(struct vector* v);
static void _vector_push_back(struct vector* v, void* elem);

struct vector* vector_init() {
    struct vector* v = (struct vector*) malloc(sizeof(struct vector));
    if (v == NULL) {
        printf("memory allocation failure, exitting!");
        exit(0x500);
    }
    v->cap = INIT_CAP;
    v->size = 0;
    v->buf = (void**) malloc(sizeof(void*) * v->cap);
    if (v->buf == NULL) {
        printf("memory allocation failure, exitting!");
        exit(0x500);
    }
    return v;
}

void vector_destroy(struct vector* v) {
    for (uint32_t i = 0; i < v->size; i++) {
        free(v->buf[i]);
    }
    free(v->buf);
    free(v);
}

void print_vec_int32(struct vector* v) {
    printf("================================\n");
    printf("vector size: %d\n", v->size);
    printf("vector cap: %d\n", v->cap);
    printf("vector content: ");
    for (uint32_t i = 0; i < v->size; i++) {
        printf("%d ", *((int32_t*)(v->buf[i])));
    }
    printf("\n");
    printf("================================\n");
}

void vector_push_back_int32(struct vector* v, int32_t elem) {
    int32_t* e = (int32_t*) malloc(sizeof(int32_t));
    *e = elem;
    _vector_push_back(v, (void*) e);
}

void vector_pop_back(struct vector* v) {
    if (v->size == 0) {
        printf("Error vector_pop_back, vector is empty");
        return;
    }
    free(v->buf[v->size - 1]);
    v->size--;
}

static void _vector_push_back(struct vector* v, void* elem) {
    if (v->size == v->cap) {
        _vector_grow(v);
    }
    v->buf[v->size] = elem;
    v->size++;
}

static void _vector_grow(struct vector* v) {
    v->buf = realloc(v->buf, sizeof(void*) * v->cap * SCALE);
    if (v->buf == NULL) {
        printf("memory allocation failure, exitting!");
        exit(0x500);
    }
    v->cap *= SCALE;
}

#endif