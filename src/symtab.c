/**
 * libmacho-1.0 - symtab.c
 * Copyright (C) 2013 Crippy-Dev Team
 * Copyright (C) 2010-2013 Joshua Hill
 * Copyright (C) 2010-2023 Joshua Minguez
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG
#include <libcrippy-1.0/debug.h>
#include <libcrippy-1.0/libcrippy.h>

#include <libmacho-1.0/symtab.h>

/*
 * Mach-O Symtab Functions
 */
macho_symtab_t_64* macho_symtab_create_64() {
	macho_symtab_t_64* symtab = malloc(sizeof(macho_symtab_t_64));
	if (symtab) {
		memset(symtab, '\0', sizeof(macho_symtab_t_64));
	}
	return symtab;
}

macho_symtab_t_64* macho_symtab_load_64(unsigned char* data, unsigned int offset) {
	int i = 0;
	macho_symtab_t_64* symtab = macho_symtab_create_64();
	if (symtab) {
		symtab->cmd = macho_symtab_cmd_load_64(&data[offset]);
		if (!symtab->cmd) {
			macho_symtab_free_64(symtab);
			return NULL;
		}
		symtab->nsyms = symtab->cmd->nsyms;
		symtab->symbols = (struct nlist*)(&data[symtab->cmd->symoff]);
		debug("Found %d symbols in symtab\n", symtab->nsyms);
		for (i = 0; i < symtab->nsyms; i++) {
			uint32_t off = symtab->symbols[i].n_un.n_strx;
			if (off >= symtab->cmd->strsize) {
				symtab->symbols[i].n_un.n_name = NULL;
			} else {
				symtab->symbols[i].n_un.n_name = (char*)(data+symtab->cmd->stroff + off);
			}
		}
		//macho_symtab_debug(symtab);
	}
	return symtab;
}

void macho_symtab_debug(macho_symtab_t_64* symtab) {
	int i = 0;
	if(symtab) {
		debug("\tSymtab:\n");
		debug("\t\tnsyms: 0x%08x\n", symtab->nsyms);
		for (i = 0; i < symtab->nsyms; i++) {
			struct nlist sym = symtab->symbols[i];
			if (sym.n_un.n_name) {
				debug("\t\t0x%x\tname=%s\n", i, sym.n_un.n_name);
			} else {
				debug("\t\t0x%x\tname=(no name)\n", i);
			}
			debug("\t\t\tn_type=0x%02x,n_sect=0x%02x,n_desc=0x%04x,n_value=0x%08x\n", sym.n_type, sym.n_sect, sym.n_desc, sym.n_value);
		}
	}
}//

void macho_symtab_free_64(macho_symtab_t_64* symtab) {
	if (symtab) {
		if (symtab->cmd) {
			macho_symtab_cmd_free_64(symtab->cmd);
		}
		free(symtab);
	}
}

/*
 * Mach-O Symtab Info Functions 
 */
macho_symtab_cmd_t_64* macho_symtab_cmd_create_64() {
	macho_symtab_cmd_t_64* info = malloc(sizeof(macho_symtab_cmd_t_64));
	if (info) {
		memset(info, '\0', sizeof(macho_symtab_cmd_t_64));
	}
	return info;
}

macho_symtab_cmd_t_64* macho_symtab_cmd_load_64(unsigned char* data) {
	macho_symtab_cmd_t_64* cmd = macho_symtab_cmd_create_64();
	if (cmd) {
		memcpy(cmd, data, sizeof(macho_symtab_cmd_t_64));
		//macho_symtab_cmd_debug(cmd);
	}
	return cmd;
}

void macho_symtab_cmd_debug_64(macho_symtab_cmd_t_64* cmd) {
	debug("\tSymtab Command:\n");
	debug("\t\t     cmd = 0x%x\n", cmd->cmd);
	debug("\t\t cmdsize = 0x%x\n", cmd->cmdsize);
	debug("\t\t  symoff = 0x%x\n", cmd->symoff);
	debug("\t\t   nsyms = 0x%x\n", cmd->nsyms);
	debug("\t\t  stroff = 0x%x\n", cmd->stroff);
	debug("\t\t strsize = 0x%x\n", cmd->strsize);
}

void macho_symtab_cmd_free_64(macho_symtab_cmd_t_64* cmd) {
	if (cmd) {
		free(cmd);
	}
}
