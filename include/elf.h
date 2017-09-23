#ifndef _ELF_H
#define _ELF_H

#include <elf-in.h>

/*  elf file class */
extern int elf_header_file_class(Elf32_Ehdr *elf);

/* elf data encoding. */
extern int elf_header_data_encoding(Elf32_Ehdr *elf);

/* elf file version */
extern int elf_header_file_version(Elf32_Ehdr *elf);

/* elf OS ABI identification */
extern int elf_header_os_ABI(Elf32_Ehdr *elf);

/* elf abi version */
extern int elf_header_ABI_version(Elf32_Ehdr *elf);

/* elf pad */
extern int elf_header_pad(Elf32_Ehdr *elf);

/* object file type */
extern int elf_header_object_file_type(Elf32_Ehdr *elf);

/* architecture for target */
extern int elf_header_arch_machine(Elf32_Ehdr *elf);

/* ELF version */
extern int elf_header_version(Elf32_Ehdr *elf);

/* get number of sections */
extern int elf_header_section_numbers(Elf32_Ehdr *elf);

/* get section header from section table */
extern Elf32_Shdr *elf_section_header_get_by_index(Elf32_Shdr *st, int index);

/* elf check */
extern int elf_header_check_magic(Elf32_Ehdr *elf);

/* alloc elf header */
extern Elf32_Ehdr *elf_header_alloc(const char *filename);

/* free elf header */
extern void elf_header_free(Elf32_Ehdr *header);

/* alloc elf section table */
extern Elf32_Shdr *elf_section_table_alloc(const char *filename);

/* free elf section table */
extern void elf_section_table_free(Elf32_Shdr *st);

/* alloc elf section header by offset */
extern Elf32_Shdr *elf_section_header_alloc_by_offset(const char *filename,
           int offset);

/* alloc elf section header by name */
extern Elf32_Shdr *elf_section_header_alloc_by_name(const char *filename,
            const char *name);

/* free elf section header */
extern void elf_section_header_free(Elf32_Shdr *st);

/* alloc section contents */
extern void *elf_section_contents_alloc(const char *filename, Elf32_Shdr *st);

/* free section contents */
extern void elf_section_contents_free(void *stc);

/* alloc section contents by offset */
extern void *elf_section_contents_alloc_by_offset(const char *filename, 
            int offset);

/* alloc section contents by name */
extern void *elf_section_contents_alloc_by_name(const char *filename,
      const char *name);

/* alloc section name */
extern char *elf_section_name_alloc(const char *filename, Elf32_Shdr *st);

/* free section name */
extern void elf_section_name_free(void *name);

#endif
