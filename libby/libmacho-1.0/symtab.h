/**
 * libmacho-1.0 - symtab.h
 * Copyright (C) 2013 Crippy-Dev Team
 * Copyright (C) 2010-2013 Joshua Hill
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef MACHO_SYMTAB_H_
#define MACHO_SYMTAB_H_

#include <libcrippy-1.0/libcrippy.h>

typedef struct macho_symtab_cmd_t_64 {
	uint64_t cmd;		/* LC_SYMTAB */
	uint64_t cmdsize;	/* sizeof(struct macho_symtab_cmd_t_64) */
	uint64_t symoff;	/* symbol table offset */
	uint64_t nsyms;		/* number of symbol table entries */
	uint64_t stroff;	/* string table offset */
	uint64_t strsize;	/* string table size in bytes */
} macho_symtab_cmd_t_64;

typedef struct nlist_64 {
	union {
		char *n_name; /* resolved symbol name */
		int64_t n_strx; /* index into the string table */
	} n_un;
	uint16_t n_type; /* type flag, see below */
	uint16_t n_sect; /* section number or NO_SECT */
	int32_t n_desc; /* see <mach-o/stab.h> */
	uint64_t n_value; /* value of this symbol (or stab offset) */
} nlist_64;

typedef struct macho_symtab_t_64 {
	uint64_t nsyms;
	struct nlist_64* symbols;
	macho_symtab_cmd_t_64* cmd;
} macho_symtab_t_64;

/*
 * Mach-O Symtab Functions
 */
macho_symtab_t_64* macho_symtab_create_64();
macho_symtab_t_64* macho_symtab_load_64(unsigned char* data, unsigned int offset);
void macho_symtab_debug_64(macho_symtab_t_64* symtab);
void macho_symtab_free_64(macho_symtab_t_64* symtab);

/*
 * Mach-O Symtab Info Functions
 */
macho_symtab_cmd_t_64* macho_symtab_cmd_create_64();
macho_symtab_cmd_t_64* macho_symtab_cmd_load_64(unsigned char* data);
void macho_symtab_cmd_debug_64(macho_symtab_cmd_t_64* cmd);
void macho_symtab_cmd_free_64(macho_symtab_cmd_t_64* cmd);

#endif /* MACHO_SYMTAB_H_ */
