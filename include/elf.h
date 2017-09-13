#ifndef _ELF_IN_H
#define _ELF_IN_H

#include <elf-in.h>

/* The elf head for current file */
extern Elf32_Ehdr *__elf_header;
/* The elf section table for current. */
extern Elf32_Shdr *__elf_section_table;
/* The file name of current */
extern char *__elf_file_name;

/* elf magic check */
extern int elf_check_magic(Elf32_Ehdr *elf);

/* elf file cleass */
extern int elf_file_class(Elf32_Ehdr *elf);

/* elf data encoding */
extern int elf_data_encoding(Elf32_Ehdr *elf);

/* elf file version */
extern int elf_file_version(Elf32_Ehdr *elf);

/* elf OS ABI identification */
extern int elf_os_ABI(Elf32_Ehdr *elf);

/* elf abi version */
extern int elf_ABI_version(Elf32_Ehdr *elf);

/* elf pad */
extern int elf_pad(Elf32_Ehdr *elf);

/* object file type */
extern int elf_object_file_type(Elf32_Ehdr *elf);

/* architecture for target */
extern int elf_arch_machine(Elf32_Ehdr *elf);

/* elf version */
extern int elf_version(Elf32_Ehdr *elf);

/* elf file name get */
extern void elf_file_name_get(char *oldname);

/* elf file name put */
extern void elf_file_name_put(void);

/* get elf header struct */
extern int elf_header_get(void);

/* put elf header struct */
extern void elf_header_put(void);

/* get elf section table */
extern int elf_section_table_get(void);

/* put elf section table */
extern void elf_section_table_put(void);

/* get elf section by index */
extern Elf32_Shdr *elf_get_section_by_index(int index);

/* load section by index */
extern void *elf_load_section_by_index(int index);

/* free section buffer */
extern void elf_section_buffer_free(void *buffer);
#endif
