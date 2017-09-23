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
static int __dump_symtab;

static const char *SECTION_FLAGS[] = {
    "CONTENTS", "ALLOC", "LOAD", "RELOC",
    "READONLY", "CODE",
};

/*
 * Dump elf headers
 */
static void dump_headers(const char *filename)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *section_table;
    int i;

    /* get elf header */
    header = elf_header_alloc(filename);
    /* get section table */
    section_table = elf_section_table_alloc(filename);

    printf("%s::     file format ", filename);
    printf("%s-%s\n", elf_header_file_class(header) ? "elf32" : "unknown",
           elf_header_arch_machine(header) ? "i386" : "unknown");

    printf("\nSections:\n");

    printf("Idx Name          Size      VMA       LMA       File off  Algn\n");
    printf("  0 NULL          00000000  00000000  00000000  00000000  0--0\n");
    for (i = 1; i < elf_header_section_numbers(header); i++) {
        /* get specify section header */
        Elf32_Shdr *st = elf_section_header_get_by_index(section_table, i);
        char *name = elf_section_name_alloc(filename, st);        
        
        /* index */
        printf("%3d ", i);
        /* section name */
        printf("%-14s", name);
        /* section size */
        printf("%08x  ", st->sh_size);
        /* vma address */
        printf("%08x  ", st->sh_addr);
        /* LMA */
        printf("%08x  ", st->sh_addr);
        /* File offset */
        printf("%08x  ", st->sh_offset);
        /* Alignment */
        printf("%d--%d", st->sh_addralign, st->sh_addralign * 2);
        printf("\n                  ");
        printf("CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE\n");
        /* free */
        elf_section_name_free(name);
    }
    elf_section_table_free(section_table);
    elf_header_free(header);
}

/* Dump symbol table */
static void dump_symtab(void)
{
    printf("Hello World.\n");
}

int main(int argc, char *argv[])
{
    const struct option long_opts[] = {
        {"headers", no_argument, NULL, 'h'},
        {"syms", no_argument, NULL, 't'},
        {0, 0, 0, 0}
    };
    const char *short_opts = "ht";
    int c;

    while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        switch (c) {
        case 'h':
            __dump_headers = 1;
            break;
        case 't':
            __dump_symtab = 1;
            break;
        default:
            abort();
        }
    }

    if (__dump_headers) {
        dump_headers(argv[argc - 1]);
    }
    if (__dump_symtab) {
        dump_symtab();
    }
    
    return 0;
}
