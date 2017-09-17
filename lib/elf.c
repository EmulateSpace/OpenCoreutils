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
#include <elf.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <xmalloc.h>
/* ----------------- 
 *   __elf_file_name
 *       | |
 *   __elf_header
 *       | |
 *   __elf_section_table
 */
 
/* The elf head for current file */
Elf32_Ehdr *__elf_header;
/* The elf section table for current. */
Elf32_Shdr *__elf_section_table;
/* The file name of current */
char *__elf_file_name = NULL;
/* Buffer of strtab */
char *__elf_strtab = NULL;


/*
 * ELF head check
 * @return: 0 if file is ELF.
 */
int elf_check_magic(Elf32_Ehdr *elf)
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
int elf_file_class(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_CLASS] & ELFCLASSNUM);
}

/*
 * elf data encoding.
 * @return: 0 invalid data encoding.
 *          1 little endian.
 *          2 big endian.
 */
int elf_data_encoding(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_DATA] & ELFDATANUM);
}

/*
 * elf file version
 * @return: file version.
 */
int elf_file_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_VERSION] & 0xff);
}

/*
 * elf OS ABI identification.
 */
int elf_os_ABI(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_OSABI] & ELFOSABI_STANDALONE);
}

/*
 * elf abi version
 */
int elf_ABI_version(Elf32_Ehdr *elf)
{
    return (elf->e_ident[EI_ABIVERSION] & 0xff);
}

/*
 * elf pad
 */
int elf_pad(Elf32_Ehdr *elf)
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
int elf_object_file_type(Elf32_Ehdr *elf)
{
    return (elf->e_type & 0x0f);
}

/*
 * architecture for target.
 * more return information refe include/elf.h EM_*
 */
int elf_arch_machine(Elf32_Ehdr *elf)
{
    return (elf->e_machine & 0xffff);
}

/*
 * ELF version
 * @return: 0 Invalid ELF version
 *          1 Current version
 */
int elf_version(Elf32_Ehdr *elf)
{
    return (elf->e_version & 0x01);
}

/*
 * get number of sections
 */
int elf_section_numbers(Elf32_Ehdr *elf)
{
    return (elf->e_shnum);
}

/*
 * elf file name store.
 */
void elf_file_name_get(char *oldname)
{
    __elf_file_name = xmalloc(strlen(oldname) + 1);
    strcpy(__elf_file_name, oldname);
}

/*
 * elf file name free
 */
void elf_file_name_put(void)
{
    if (!__elf_file_name)
        xfree(__elf_file_name);
    __elf_file_name = NULL;
}

/*
 * Get elf header struct.
 */
int elf_header_get(void)
{
    int fd;

    if (!__elf_file_name)
        return -ENODEV;

    /* allocate memory for elf_header */
    __elf_header = xmalloc(sizeof(*__elf_header));
    memset(__elf_header, 0, sizeof(*__elf_header));

    fd = open(__elf_file_name, O_RDONLY, 0444);
    if (!fd)
        return -ENODEV;
    read(fd, __elf_header, sizeof(*__elf_header));
    close(fd);
    return 0;
}

/*
 * put elf header.
 */
void elf_header_put(void)
{
    if (!__elf_header)
        xfree(__elf_header);
    __elf_header = NULL;
}

/*
 * get elf section table.
 */
int elf_section_table_get(void)
{
    int fd;

    if (!__elf_file_name)
        return -ENODEV;

    if (!__elf_header)
        elf_header_get();

    /* Allocate memory for elf section table */
    __elf_section_table = xmalloc(__elf_header->e_shentsize *
                                  __elf_header->e_shnum);
    memset(__elf_section_table, 0, __elf_header->e_shentsize *
                                   __elf_header->e_shnum);

    fd = open(__elf_file_name, O_RDONLY, 0444);
    if (!fd)
        return -ENODEV;
    lseek(fd, __elf_header->e_shoff, SEEK_SET);
    read(fd, __elf_section_table, __elf_header->e_shentsize *
                                  __elf_header->e_shnum);
#ifdef CONFIG_ELF_BUFFER_STRTAB
    /* locate strtab on file */
    lseek(fd, 
          __elf_section_table[__elf_header->e_shstrndx].sh_offset, SEEK_SET);
    /* allocate memory for .strtab buffer*/
    __elf_strtab = xmalloc(
          __elf_section_table[__elf_header->e_shstrndx].sh_size);
    /* load elf string table section from file */
    read(fd, __elf_strtab, 
          __elf_section_table[__elf_header->e_shstrndx].sh_size);
#endif

    close(fd);
    return 0;
}

/*
 * put elf section table.
 */
void elf_section_table_put(void)
{
    if (__elf_strtab)
        xfree(__elf_strtab);
    __elf_strtab = NULL;
    if (__elf_section_table)
        xfree(__elf_section_table);
    __elf_section_table = NULL;
}

/*
 * get elf section by index
 * @index: index of section table for section
 *
 * @return: Elf32_Shdr
 */
Elf32_Shdr *elf_get_section_by_index(int index)
{
    return ((Elf32_Shdr *)(__elf_section_table) + index);
}

/*
 * load setion by index
 * @index:      Index of section on section table.
 *
 * @return: the buffer of section contents.
 */
void *elf_load_section_by_index(int index)
{
    size_t offset;
    char *buffer;
    int fd;
    Elf32_Shdr *st = elf_get_section_by_index(index);

    /* allocate buffer */
    buffer = xmalloc(st->sh_size);
    memset(buffer, 0, st->sh_size);

    /* offset on file */
    offset = st->sh_offset;
    fd = open(__elf_file_name, O_RDONLY, 0444);
    if (!fd)
        return -ENODEV;
    lseek(fd, offset, SEEK_SET);
    read(fd, buffer, st->sh_size);
    return buffer;
}

/*
 * free section buffer
 */
void elf_free_section(void *buffer)
{
    if (!buffer)
        xfree(buffer);
}

/*
 * get section name by index.
 * @index: sh_name on Elf32_Shdr
 */
const char *elf_get_section_name_by_index(int index)
{
#ifndef CONFIG_ELF_BUFFER_STRTAB
    char *first = NULL;
    char *dest  = NULL;
    int locate;

    /* get index of string table */
    __elf_strtab = elf_load_section_by_index(__elf_header->e_shstrndx);
    /* get first character address of string. */
    first = &__elf_strtab[index];
    /* locate end character */
    locate = strchr(first, '\0');
    /* allocate memory fo name */
    dest = xmalloc(locate * sizeof(char) + 1);
    /* dumplicate contents to new string */
    strncpy(dest, first, locate + 1);
    /* free section */
    xfree(__elf_strtab);
    __elf_strtab = NULL;
    return (dest);
#endif
    if (!__elf_strtab)
        return -EINVAL;
    /* get frist char of specify string */
    return (&__elf_strtab[index]);
}

/* 
 * free section name 
 */
void elf_free_section_name(const char *name)
{
#ifndef CONFIG_ELF_BUFFER_STRTAB
    if (name)
        xfree(name);
#endif
}

















