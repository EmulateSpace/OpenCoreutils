/*
 * elf api
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
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <xmalloc.h>
#include <elf.h>
/* --------------------------------------- 
 *   elf file (const char *)
 *       | | 
 *   elf header (Elf32_Ehdr)
 *       | |
 *   elf section table (Elf32_Shdr[])
 *       | |
 *   elf section header (Elf32_Shdr)
 *       | |
 *   elf section contents (void *)
 * ---------------------------------------
 */

/*
 * ELF head check
 * @return: 0 if file is ELF.
 */
int elf_header_check_magic(Elf32_Ehdr *elf)
{
    if (strncmp((char *)elf->e_ident, ELFMAG, 4) != 0)
        return -EINVAL;
    return 0;
}

/*
 * elf file class
 * @return: 0 invalid class
 *          1 file is 32-bit class
 *          2 file is 64-bit class
 */
int elf_header_file_class(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_CLASS] & ELFCLASSNUM);
}

/*
 * elf data encoding.
 * @return: 0 invalid data encoding.
 *          1 little endian.
 *          2 big endian.
 */
int elf_header_data_encoding(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_DATA] & ELFDATANUM);
}

/*
 * elf file version
 * @return: file version.
 */
int elf_header_file_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_VERSION] & 0xff);
}

/*
 * elf OS ABI identification.
 */
int elf_header_os_ABI(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_OSABI] & ELFOSABI_STANDALONE);
}

/*
 * elf abi version
 */
int elf_header_ABI_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_ABIVERSION] & 0xff);
}

/*
 * elf pad
 */
int elf_header_pad(Elf32_Ehdr *elf)
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
int elf_header_object_file_type(Elf32_Ehdr *elf)
{
    return (elf->e_type & 0x0f);
}

/*
 * architecture for target.
 * more return information refe include/elf.h EM_*
 */
int elf_header_arch_machine(Elf32_Ehdr *elf)
{
    return (elf->e_machine & 0xffff);
}

/*
 * ELF version
 * @return: 0 Invalid ELF version
 *          1 Current version
 */
int elf_header_version(Elf32_Ehdr *elf)
{
    return (elf->e_version & 0x01);
}

/*
 * get number of sections
 * @elf: Section header
 *
 * @return: the number of section headers on section table.
 */
int elf_header_section_numbers(Elf32_Ehdr *elf)
{
    return (elf->e_shnum);
}

/*
 * get section header from section table
 * @st: section table
 * @index: offset on section table.
 *
 * @return: Elf section header.
 */
Elf32_Shdr *elf_section_header_get_by_index(Elf32_Shdr *st, int index)
{
    return (st) + index;
}

/* (OK)
 * alloc elf header struct for specify file.
 * @filename: file name.
 *
 * @return: Elf32 header.
 */
Elf32_Ehdr *elf_header_alloc(const char *filename)
{
    int fd;
    Elf32_Ehdr *tmp_header;

    /* allocate memory for elf_header */
    tmp_header = xmalloc(sizeof(Elf32_Ehdr));
    memset(tmp_header, 0, sizeof(Elf32_Ehdr));

    fd = open(filename, O_RDONLY, 0444);
    if (!fd)
        return NULL;
    read(fd, tmp_header, sizeof(Elf32_Ehdr));
    close(fd);
    return tmp_header;
}

/* (OK)
 * free elf32_Ehdr
 * @header: Elf32 Header
 */
void elf_header_free(Elf32_Ehdr *header)
{
    xfree(header);
}

/* (OK)
 * get elf section table for specify file.
 * @filename: specify file.
 * 
 * @return: elf section table for elf file
 */
Elf32_Shdr *elf_section_table_alloc(const char *filename)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *st;
    int fd;

    /* get elf header for file */
    header = elf_header_alloc(filename);

    /* Allocate memory for elf section table */
    st = xmalloc(header->e_shentsize * header->e_shnum);
    memset(st, 0, header->e_shentsize * header->e_shnum);

    /* load contents from file */
    fd = open(filename, O_RDONLY, 0444);
    if (!fd)
        return NULL;
    lseek(fd, header->e_shoff, SEEK_SET);
    read(fd, st, header->e_shentsize * header->e_shnum);
    /* exit */
    close(fd);
    elf_header_free(header);
    return st;
}

/* (OK)
 * free section table
 * @st: elf section table.
 */
void elf_section_table_free(Elf32_Shdr *st)
{
    xfree(st);
}

/* (OK)
 * dumplicate section header
 */
static void elf_section_header_dumplicate(Elf32_Shdr *new, Elf32_Shdr *old)
{
    new->sh_name = old->sh_name;
    new->sh_type = old->sh_type;
    new->sh_flags = old->sh_flags;
    new->sh_addr = old->sh_addr;
    new->sh_offset = old->sh_offset;
    new->sh_size = old->sh_size;
    new->sh_link = old->sh_link;
    new->sh_info = old->sh_info;
    new->sh_addralign = old->sh_addralign;
    new->sh_entsize = old->sh_entsize;
}

/* (OK)
 * get elf section header by offset from section table.
 * @filename: elf file
 * @offset: offset of section table for section
 *
 * @return: section header
 */
Elf32_Shdr *elf_section_header_alloc_by_offset(const char *filename, 
           int offset)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *st;
    Elf32_Shdr *tmp, *tmp1;

    header = elf_header_alloc(filename);
    if (offset < 0 || offset > elf_header_section_numbers(header)) {
        elf_header_free(header);
        return NULL;
    }

    /* get section table */
    st = elf_section_table_alloc(filename);
    tmp1 = elf_section_header_get_by_index(st, offset);
    /* create a new elf section header */
    tmp = xmalloc(sizeof(Elf32_Shdr));
    memset(tmp, 0, sizeof(Elf32_Shdr));

    /* dumplicate from section table */
    elf_section_header_dumplicate(tmp, tmp1);
    /* free section table */
    elf_section_table_free(st);
    elf_header_free(header);
    return tmp;
}

/* (OK)
 * get elf section by section name
 * @name: section name
 *
 * @return: Elf32_Shdr
 */
Elf32_Shdr *elf_section_header_alloc_by_name(const char *filename, 
            const char *name)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *section_table;
    Elf32_Shdr *tmp = NULL;
    int i;

    /* get elf header */
    header = elf_header_alloc(filename);
    /* get elf section table */
    section_table = elf_section_table_alloc(filename);

    for(i = 1; i < elf_header_section_numbers(header); i++) {
        /* current section */
        Elf32_Shdr *st = elf_section_header_get_by_index(section_table, i);
        char *st_name;

        /* get section name */
        st_name = elf_section_name_alloc(filename, st);
        /* Compare string */
        if (strcmp(st_name, name) == 0) {
            /* create new section header */
            tmp = xmalloc(sizeof(Elf32_Shdr));
            memset(tmp, 0, sizeof(Elf32_Shdr));
            /* dumplicate contents */
            elf_section_header_dumplicate(tmp, st);
            break;
        }
        elf_section_name_free(st_name);
    }
    /* Release resource */
    elf_header_free(header);
    elf_section_table_free(section_table);
    return tmp;
}

/* (OK)
 * free elf setcion header
 * @header: Elf32 section header
 */
void elf_section_header_free(Elf32_Shdr *st)
{
    xfree(st);
}

/* (OK)
 * load section contents
 * @filename: elf file name
 * @st: Elf32 section header
 *
 * @return: the buffer of section contents.
 */
void *elf_section_contents_alloc(const char *filename, Elf32_Shdr *st)
{
    char *buffer;
    int fd;

    /* allocate buffer */
    buffer = xmalloc(st->sh_size);
    memset(buffer, 0, st->sh_size);

    fd = open(filename, O_RDONLY, 0444);
    if (!fd)
        return NULL;
    lseek(fd, st->sh_offset, SEEK_SET);
    read(fd, buffer, st->sh_size);
    return buffer;
}

/* (OK) 
 * free section contents
 * @stc: section contents
 */
void elf_section_contents_free(void *stc)
{
    xfree(stc);
}

/* (OK)
 * load section contents by offset
 * @filename: elf file name
 * @offset: offset on section table
 *
 * @return: the buffer of section contents.
 */
void *elf_section_contents_alloc_by_offset(const char *filename, int offset)
{
    Elf32_Shdr *tmp = elf_section_header_alloc_by_offset(filename, offset);
    char *buffer;

    buffer = elf_section_contents_alloc(filename, tmp);
    /* free Elf32_Shdr */
    elf_section_header_free(tmp);
    return buffer; 
}

/* (OK)
 * load section contents by name
 * @filename: elf file name
 * @name: section header name.
 *
 * @return: contents of section
 */
void *elf_section_contents_alloc_by_name(const char *filename, 
      const char *name)
{
    Elf32_Shdr *tmp = elf_section_header_alloc_by_name(filename, name);
    char *buffer;

    buffer = elf_section_contents_alloc(filename, tmp);
    /* free Elf32_Shdr */
    elf_section_header_free(tmp);
    return buffer;
}

/* (OK)
 * alloc section name
 * @filename: elf file name
 * @st: section header
 *
 * @return: section name
 */
char *elf_section_name_alloc(const char *filename, Elf32_Shdr *st)
{
    Elf32_Ehdr *header;
    Elf32_Shdr *section_table;
    Elf32_Shdr *strtab;
    char *contents;
    char *tmp1, *tmp2;

    /* get elf header */
    header = elf_header_alloc(filename);
    /* get elf section table */
    section_table = elf_section_table_alloc(filename);
    /* get section header for .strtab */
    strtab = elf_section_header_get_by_index(section_table, 
                                             header->e_shstrndx);
    /* get section contents for .strtab */
    contents = elf_section_contents_alloc(filename, strtab); 
    /* get section name */
    tmp1 = contents + st->sh_name;
    /* create new name */
    tmp2 = xmalloc(strlen(tmp1) + 1);
    memset(tmp2, 0, strlen(tmp1) + 1);
    /* dumplcate name from strtab */
    strncpy(tmp2, tmp1, strlen(tmp1) + 1);

    elf_section_contents_free(contents);
    elf_section_table_free(section_table);
    elf_header_free(header);
    return tmp2;
}

/* (OK)
 * free section name
 * @name: section name
 */
void elf_section_name_free(void *name)
{
    xfree(name);
}
