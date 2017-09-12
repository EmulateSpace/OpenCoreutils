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
#include <string.h>

#include <xmalloc.h>
#include <elf.h>

#define HEADERS_SIZE  1024

/* global options */
static int __section_headers;
static Elf32_Ehdr *file_header;

/*
 * create ELF header struct.
 */
static int create_file_header(const char *filename)
{
    int fd;

    file_header = xmalloc(sizeof(*file_header));
    memset(file_header, 0, sizeof(*file_header));
    fd = open(filename, O_RDONLY);
    if (!fd)
        exit(EXIT_FAILURE);
    read(fd, (char *)(unsigned long)file_header, sizeof(*file_header));
    close(fd);
    return 0;
}

/*
 * Destroy ELF header.
 */
void destroy_file_header(void)
{
    xfree(file_header);
}

static int dump_section_headers(const char *filename)
{
    int i;

    create_file_header(filename);
    
    printf("machine %d\n", file_header->e_machine);
    destroy_file_header();
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
