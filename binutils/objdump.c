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
static void destroy_file_header(void)
{
    xfree(file_header);
}

/*
 * ELF head check
 * @return: 0 if file is ELF.
 */
static int elf_check_magic(Elf32_Ehdr *elf)
{
    if (strncmp(elf->e_ident, ELFMAG, 4) != 0)
        return -EINVAL;
    return 0;
}

/*
 * elf file class
 * @return: 0 invalid class
 *          1 file is 32-bit class
 *          2 file is 64-bit class
 */
static int elf_file_class(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_CLASS] & ELFCLASSNUM);
}

/*
 * elf data encoding.
 * @return: 0 invalid data encoding.
 *          1 little endian.
 *          2 big endian.
 */
static int elf_data_encoding(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_DATA] & ELFDATANUM);
}

/*
 * elf file version
 * @return: file version.
 */
static int elf_file_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_VERSION] & 0xff);
}

/*
 * elf OS ABI identification.
 */
static int elf_os_ABI(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_OSABI] & ELFOSABI_STANDALONE);
}

/*
 * elf abi version
 */
static int elf_ABI_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_ABIVERSION] & 0xff);
}

/*
 * elf pad
 */
static int elf_pad(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_PAD] & 0xff);
}

/*
 * object file type.
 * @return: 0 No file type.
 *          1 Relocatable file.
 *          2 Executable file.
 *          3 Shared object file.
 *          4 Core file
 */
static int elf_object_file_type(Elf32_Ehdr *elf)
{
    return (elf->e_type & 0x0f);
}

/*
 * architecture for target.
 * more return information refe include/elf.h EM_*
 */
static int elf_arch_machine(Elf32_Ehdr *elf)
{
    return (elf->e_machine & 0xffff);
}

/*
 * ELF version
 * @return: 0 Invalid ELF version
 *          1 Current version
 */
static int elf_version(Elf32_Ehdr *elf)
{
    return (elf->e_version & 0x01);
}

static int dump_section_headers(const char *filename)
{
    int i;

    create_file_header(filename);
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
