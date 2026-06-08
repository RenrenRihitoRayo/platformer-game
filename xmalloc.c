#include "renplat.h"
#include <stdlib.h>
#include <stdio.h>

void* xmalloc(size_t size)
{
    void* data = malloc(size);
    if (!data) {
        fprintf(stderr, "allocation OOM.\n");
        abort();
    }
    return data;
}
