/*
 * objdump
 *
 * (C) 2017.09 <buddy.zhang@aliyun.com>
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/>
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include <elf.h>
#include <xmalloc.h>

static int __dump_headers;

/*
 * Dump elf headers
 */
static void dump_headers(void)
{
    int i;

    /* Dump file name, file class and target machine */
    printf("%s:     file format elf%s-%s\n\n", __elf_file_name,
            elf_file_class(__elf_header) ? "32" : "64",
            elf_arch_machine(__elf_header) ? "i386": "x86");

    /* Dump section */
    printf("Sections:\n");
    printf("Idx Name          Size      VMA       LMA       File off  Algn\n");
    for (i = 0; i < elf_section_numbers(__elf_header); i++) {
        /* get section table describe */
        Elf32_Shdr *st = elf_get_section_by_index(i);
        char *section_name = elf_get_section_name_by_index(st->sh_name);

        /* first string table is NULL */
        if (i == 0) {
            printf("%3d  NULL\n", i);
            continue;
        }

        /* dump base section info */
        printf("%3d %-13s %08x  %08x  %08x  %08x  %d**%d\n", i, 
               section_name, st->sh_size, st->sh_addr, st->sh_addr, 
               st->sh_offset, st->sh_addralign, st->sh_addralign);
        

        /* free section name in the end */
        xfree(section_name);
    }    
}

/* Initialize objdump tools */
static int objdump_init(const char *filename)
{
    /* Setup file name */
    elf_file_name_get(filename);
    /* Setup elf header */
    elf_header_get();
    /* Setup elf section tables */
    elf_section_table_get();
    return 0;
}

/* Exit objdump tools */
static void objdump_exit(void)
{
    /* Remove elf section tables */
    elf_section_table_put();
    /* Remove elf header */
    elf_header_put();
    /* Remove file name */
    elf_file_name_put();
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
            __dump_headers = 1;
            break;
        default:
            abort();
        }
    }
    /* initalize objdump */
    objdump_init(argv[argc - 1]);

    if (__dump_headers) {
        dump_headers();
    }
    
    /* exit objdump */
    objdump_exit();
    return 0;
}
