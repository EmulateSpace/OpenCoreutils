/*
 * objdump
 *
 * (C) 2017.09 <buddy.zhang@aliyun.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <xmalloc.h>

#define HEADERS_SIZE  1024

/* global options */
static int __section_headers;

static int dump_section_headers(const char *filename)
{
    char *buffer;
    int fd;
    int i;

    buffer = xmalloc(HEADERS_SIZE);
    fd = open(filename, O_RDONLY);
    if (!fd)
        return -ENODEV;
    read(fd, buffer, HEADERS_SIZE);

    for (i = 0; i < 10; i++)
        printf(" %d ", buffer[i]);
    printf("\n");

    xfree(buffer);
    close(fd);
    return 0;
}

int main(int argc, char **argv[])
{
    const struct option long_opts[] = {
        {"headers", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };
    const char *short_opts = "h";
    int c;

    while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        switch (c) {
        case 'h':
            __section_headers = 1;
            break;
        default:
            abort();
        }
    }

    if (__section_headers) {
        dump_section_headers(argv[argc - 1]);
    }
    return 0;
}
