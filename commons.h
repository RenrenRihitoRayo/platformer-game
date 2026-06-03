#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Allocate 'size' bytes
void* xmalloc(size_t size) {
    void* data = malloc(size);
    if (!data) {
        fprintf(stderr, "xmalloc: Allocation failed!");
        abort();
    }
    return data;
}

#define da_growth_rate 0.75
#define da_grow(x) x+(x*da_growth_rate)

#define da_debug(arr)\
    printf("Debug for Dynamic Array " #arr "\nSize: %i\nCount: %i\n", arr->size, arr->count);

typedef struct {
    void** items;
    uint32_t count, size;
} __da_type_mask;

static inline void da_append(void* dyn_array, void* item) {
    __da_type_mask* arr = (__da_type_mask*)dyn_array;
    if (arr == NULL) {
        fprintf(stderr, "The arrays NULL idiot.\n");
        abort();
    }
    else if (arr->items == NULL) { 
        arr->items = (void**)xmalloc(sizeof(void*));
        arr->items[0] = item; 
        arr->count = 1; 
        arr->size = 1;
        return;
    } else if (arr->count == 0) {
        uint32_t new_size = 10;
        arr->items = (void**)calloc(sizeof(void*), new_size);
        arr->size = new_size;
    } else if (arr->count >= arr->size) {
        uint32_t new_size = da_grow(arr->size)+1;
        arr->items = (void**)realloc(arr->items, sizeof(void*)*new_size);
        arr->size = new_size;
    }
    arr->items[arr->count++] = item;
}

static inline void da_free(void* dyn_array) {
    __da_type_mask* arr = (__da_type_mask*)dyn_array;
    for (uint32_t i=0; i<arr->count; ++i)
        free(arr->items[i]);
    free(arr->items);
    arr->items = NULL;
    arr->count = 0;
    arr->size = 0;
}