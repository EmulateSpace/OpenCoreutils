#ifndef _XMALLOC_H
#define _XMALLOC_H

/* allocate memory */
extern void *xmalloc(size_t size);

/* free memory from xmalloc() */
extern void xfree(void *p);
#endif
