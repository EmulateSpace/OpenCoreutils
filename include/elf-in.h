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

/* Fields in the e_ident array. The EI_* macros are indices into the 
   array. The macros under each EI_* macro are the value the byte
   may have. */
#define EI_MAG0           0             /* File identification byte 0 index */
#define ELFMAG0           0x7f          /* Magic number byte 0 */

#define EI_MAG1           1             /* File identification byte 1 index */
#define ELFMAG1           'E'           /* Magic number byte 1 */

#define EI_MAG3           2             /* File identification byte 2 index */
#define ELFMAG3           'F'           /* Magic number byte 3 */

/* Conglomeration of the identification bytes, for easy testing as a word */
#define ELFMAG            "\177ELF"
#define SELFMAG           4

#define EI_CLASS          4             /* File class byte index */
#define ELFCLASSNONE      0             /* Invalid class */
#define ELFCLASS32        1             /* 32-bit object */
#define ELFCLASS64        2             /* 64-bit object */
#define ELFCLASSNUM       3

#define EI_DATA           5             /* Data encoding byte index */
#define ELFDATANONE       0             /* Invalid data encoding */
#define ELFDATA2LSB       1             /* 2's complement, little endian */
#define ELFDATA2MSB       2             /* 2's complement, big endian */
#define ELFDATANUM        3

#define EI_VERSION        6             /* File version byte index */
                                        /* Value must be EV_CURRENT */

#define EI_OSABI                7       /* OS ABI identification */
#define ELFOSABI_NONE           0       /* UNIX System V ABI */
#define ELFOSABI_SYSV           0       /* Alias.  */
#define ELFOSABI_HPUX           1       /* HP-UX */
#define ELFOSABI_NETBSD         2       /* NetBSD.  */
#define ELFOSABI_GNU            3       /* Object uses GNU ELF extensions.  */
#define ELFOSABI_LINUX          ELFOSABI_GNU /* Compatibility alias.  */
#define ELFOSABI_SOLARIS        6       /* Sun Solaris.  */
#define ELFOSABI_AIX            7       /* IBM AIX.  */
#define ELFOSABI_IRIX           8       /* SGI Irix.  */
#define ELFOSABI_FREEBSD        9       /* FreeBSD.  */
#define ELFOSABI_TRU64          10      /* Compaq TRU64 UNIX.  */
#define ELFOSABI_MODESTO        11      /* Novell Modesto.  */
#define ELFOSABI_OPENBSD        12      /* OpenBSD.  */
#define ELFOSABI_ARM_AEABI      64      /* ARM EABI */
#define ELFOSABI_ARM            97      /* ARM */
#define ELFOSABI_STANDALONE     255     /* Standalone (embedded) application */

#define EI_ABIVERSION           8       /* ABI version */

#define EI_PAD                  9       /* Byte index of padding bytes */

/* Legal values for e_type (object file type).  */

#define ET_NONE         0               /* No file type */
#define ET_REL          1               /* Relocatable file */
#define ET_EXEC         2               /* Executable file */
#define ET_DYN          3               /* Shared object file */
#define ET_CORE         4               /* Core file */
#define ET_NUM          5               /* Number of defined types */
#define ET_LOOS         0xfe00          /* OS-specific range start */
#define ET_HIOS         0xfeff          /* OS-specific range end */
#define ET_LOPROC       0xff00          /* Processor-specific range start */
#define ET_HIPROC       0xffff          /* Processor-specific range end */

/* Legal values for e_machine (architecture).  */

#define EM_NONE          0              /* No machine */
#define EM_M32           1              /* AT&T WE 32100 */
#define EM_SPARC         2              /* SUN SPARC */
#define EM_386           3              /* Intel 80386 */
#define EM_68K           4              /* Motorola m68k family */
#define EM_88K           5              /* Motorola m88k family */
#define EM_860           7              /* Intel 80860 */
#define EM_MIPS          8              /* MIPS R3000 big-endian */
#define EM_S370          9              /* IBM System/370 */
#define EM_MIPS_RS3_LE  10              /* MIPS R3000 little-endian */

#define EM_PARISC       15              /* HPPA */
#define EM_VPP500       17              /* Fujitsu VPP500 */
#define EM_SPARC32PLUS  18              /* Sun's "v8plus" */
#define EM_960          19              /* Intel 80960 */
#define EM_PPC          20              /* PowerPC */
#define EM_PPC64        21              /* PowerPC 64-bit */
#define EM_S390         22              /* IBM S390 */

#define EM_V800         36              /* NEC V800 series */
#define EM_FR20         37              /* Fujitsu FR20 */
#define EM_RH32         38              /* TRW RH-32 */
#define EM_RCE          39              /* Motorola RCE */
#define EM_ARM          40              /* ARM */
#define EM_FAKE_ALPHA   41              /* Digital Alpha */
#define EM_SH           42              /* Hitachi SH */
#define EM_SPARCV9      43              /* SPARC v9 64-bit */
#define EM_TRICORE      44              /* Siemens Tricore */
#define EM_ARC          45              /* Argonaut RISC Core */
#define EM_H8_300       46              /* Hitachi H8/300 */
#define EM_H8_300H      47              /* Hitachi H8/300H */
#define EM_H8S          48              /* Hitachi H8S */
#define EM_H8_500       49              /* Hitachi H8/500 */
#define EM_IA_64        50              /* Intel Merced */
#define EM_MIPS_X       51              /* Stanford MIPS-X */
#define EM_COLDFIRE     52              /* Motorola Coldfire */
#define EM_68HC12       53              /* Motorola M68HC12 */
#define EM_MMA          54              /* Fujitsu MMA Multimedia Accelerator*/
#define EM_PCP          55              /* Siemens PCP */
#define EM_NCPU         56              /* Sony nCPU embeeded RISC */
#define EM_NDR1         57              /* Denso NDR1 microprocessor */
#define EM_STARCORE     58              /* Motorola Start*Core processor */
#define EM_ME16         59              /* Toyota ME16 processor */
#define EM_ST100        60              /* STMicroelectronic ST100 processor */
#define EM_TINYJ        61              /* Advanced Logic Corp. Tinyj emb.fam*/
#define EM_X86_64       62              /* AMD x86-64 architecture */
#define EM_PDSP         63              /* Sony DSP Processor */

#define EM_FX66         66              /* Siemens FX66 microcontroller */
#define EM_ST9PLUS      67              /* STMicroelectronics ST9+ 8/16 mc */
#define EM_ST7          68              /* STmicroelectronics ST7 8 bit mc */
#define EM_68HC16       69              /* Motorola MC68HC16 microcontroller */
#define EM_68HC11       70              /* Motorola MC68HC11 microcontroller */
#define EM_68HC08       71              /* Motorola MC68HC08 microcontroller */
#define EM_68HC05       72              /* Motorola MC68HC05 microcontroller */
#define EM_SVX          73              /* Silicon Graphics SVx */
#define EM_ST19         74              /* STMicroelectronics ST19 8 bit mc */
#define EM_VAX          75              /* Digital VAX */
#define EM_CRIS         76              /* Axis Communications 32-bit embedded processor */
#define EM_JAVELIN      77              /* Infineon Technologies 32-bit embedded processor */
#define EM_FIREPATH     78              /* Element 14 64-bit DSP Processor */
#define EM_ZSP          79              /* LSI Logic 16-bit DSP Processor */
#define EM_MMIX         80              /* Donald Knuth's educational 64-bit processor */
#define EM_HUANY        81              /* Harvard University machine-independent object files */
#define EM_PRISM        82              /* SiTera Prism */
#define EM_AVR          83              /* Atmel AVR 8-bit microcontroller */
#define EM_FR30         84              /* Fujitsu FR30 */
#define EM_D10V         85              /* Mitsubishi D10V */
#define EM_D30V         86              /* Mitsubishi D30V */
#define EM_V850         87              /* NEC v850 */
#define EM_M32R         88              /* Mitsubishi M32R */
#define EM_MN10300      89              /* Matsushita MN10300 */
#define EM_MN10200      90              /* Matsushita MN10200 */
#define EM_PJ           91              /* picoJava */
#define EM_OPENRISC     92              /* OpenRISC 32-bit embedded processor */
#define EM_ARC_A5       93              /* ARC Cores Tangent-A5 */
#define EM_XTENSA       94              /* Tensilica Xtensa Architecture */
#define EM_ALTERA_NIOS2 113             /* Altera Nios II */
#define EM_AARCH64      183             /* ARM AARCH64 */
#define EM_TILEPRO      188             /* Tilera TILEPro */
#define EM_MICROBLAZE   189             /* Xilinx MicroBlaze */
#define EM_TILEGX       191             /* Tilera TILE-Gx */
#define EM_NUM          192

/* If it is necessary to assign new unofficial EM_* values, please
   pick large random numbers (0x8523, 0xa7f2, etc.) to minimize the
   chances of collision with official or non-GNU unofficial values.  */

#define EM_ALPHA        0x9026

/* Legal values for e_version (version).  */

#define EV_NONE         0               /* Invalid ELF version */
#define EV_CURRENT      1               /* Current version */
#define EV_NUM          2

/* Section header. */

typedef struct
{
    Elf32_Word    sh_name;          /* Section name (string tbl index) */
    Elf32_Word    sh_type;          /* Section type */
    Elf32_Word    sh_flags;         /* Section flags */
    Elf32_Addr    sh_addr;          /* Section virtual addr at execution */
    Elf32_Off     sh_offset;        /* Section file offset */
    Elf32_Word    sh_size;          /* Section size in bytes */
    Elf32_Word    sh_link;          /* link to another section */
    Elf32_Word    sh_info;          /* Additional section information */
    Elf32_Word    sh_addralign;     /* Section alignment */
    Elf32_Word    sh_entsize;       /* Entry size if section holds table */
} Elf32_Shdr;

/* Legal values for sh_type (section type).  */

#define SHT_NULL          0             /* Section header table entry unused */
#define SHT_PROGBITS      1             /* Program data */
#define SHT_SYMTAB        2             /* Symbol table */
#define SHT_STRTAB        3             /* String table */
#define SHT_RELA          4             /* Relocation entries with addends */
#define SHT_HASH          5             /* Symbol hash table */
#define SHT_DYNAMIC       6             /* Dynamic linking information */
#define SHT_NOTE          7             /* Notes */
#define SHT_NOBITS        8             /* Program space with no data (bss) */
#define SHT_REL           9             /* Relocation entries, no addends */
#define SHT_SHLIB         10            /* Reserved */
#define SHT_DYNSYM        11            /* Dynamic linker symbol table */
#define SHT_INIT_ARRAY    14            /* Array of constructors */
#define SHT_FINI_ARRAY    15            /* Array of destructors */
#define SHT_PREINIT_ARRAY 16            /* Array of pre-constructors */
#define SHT_GROUP         17            /* Section group */
#define SHT_SYMTAB_SHNDX  18            /* Extended section indeces */
#define SHT_NUM           19            /* Number of defined types.  */
#define SHT_LOOS          0x60000000    /* Start OS-specific.  */
#define SHT_GNU_ATTRIBUTES 0x6ffffff5   /* Object attributes.  */
#define SHT_GNU_HASH      0x6ffffff6    /* GNU-style hash table.  */
#define SHT_GNU_LIBLIST   0x6ffffff7    /* Prelink library list */
#define SHT_CHECKSUM      0x6ffffff8    /* Checksum for DSO content.  */
#define SHT_LOSUNW        0x6ffffffa    /* Sun-specific low bound.  */
#define SHT_SUNW_move     0x6ffffffa
#define SHT_SUNW_COMDAT   0x6ffffffb
#define SHT_SUNW_syminfo  0x6ffffffc
#define SHT_GNU_verdef    0x6ffffffd    /* Version definition section.  */
#define SHT_GNU_verneed   0x6ffffffe    /* Version needs section.  */
#define SHT_GNU_versym    0x6fffffff    /* Version symbol table.  */
#define SHT_HISUNW        0x6fffffff    /* Sun-specific high bound.  */
#define SHT_HIOS          0x6fffffff    /* End OS-specific type */
#define SHT_LOPROC        0x70000000    /* Start of processor-specific */
#define SHT_HIPROC        0x7fffffff    /* End of processor-specific */
#define SHT_LOUSER        0x80000000    /* Start of application-specific */
#define SHT_HIUSER        0x8fffffff    /* End of application-specific */


#endif
