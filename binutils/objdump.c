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

static int __section_headers;

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
            __section_headers = 1;
            break;
        default:
            abort();
        }
    }
    /* initalize objdump */
    objdump_init(argv[argc - 1]);

    if (__section_headers) {
    }
    
    /* exit objdump */
    objdump_exit();
    return 0;
}
