/*
 * This file defines standard ELF types, structures, and macros.
 * Copyright (C) 1995-2014 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * The GNU C Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _ELF_H
#define _ELF_H

#include <stdint.h>

/* Type for a 16-bit quantity */
typedef uint16_t Elf32_Half; 

/* Types for signed and unsigned 32-bit quantities. */
typedef uint32_t Elf32_Word;

/* Type of address. */
typedef uint32_t Elf32_Addr;

/* Type of file offsets. */
typedef uint32_t Elf32_Off;

/* The ELF file header. This appears at the start of every ELF file. */
#define EI_NIDENT (16)

typedef struct
{
    unsigned char e_ident[EI_NIDENT];    /* Magic number and other info */
    Elf32_Half    e_type;                /* Object file type */
    Elf32_Half    e_machine;             /* Architecture */
    Elf32_Word    e_version;             /* Object file version */
    Elf32_Addr    e_entry;               /* Entry point virtual address */
    Elf32_Off     e_phoff;               /* Program header table file offset */
    Elf32_Off     e_shoff;               /* Section header table file offset */
    Elf32_Word    e_flags;               /* Processor-specific flags */
    Elf32_Half    e_ehsize;              /* ELF header size in bytes */
    Elf32_Half    e_phentsize;           /* Program header table entry size */
    Elf32_Half    e_phnum;               /* Program header table entry count */
    Elf32_Half    e_shentsize;           /* Section header table entry size */
    Elf32_Half    e_shnum;               /* Section header table entry count */
    Elf32_Half    e_shstrndx;            /* Section header string table index */
} Elf32_Ehdr;

#endif
