/*
 * xmalloc.c
 *
 * (C) 2017.09 <buddy.zhang@aliyun.com>
 *
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include <xmalloc.h>

void *xmalloc(size_t size)
{
    void *alloc = malloc(size);

    if (!alloc) {
        printf("out of memory(malloc)\n");
        exit(EXIT_FAILURE);
    }
    return alloc;
}

void xfree(void *p)
{
    free(p);
}
