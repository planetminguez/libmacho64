/**
 * libmacho-1.0 - command.h
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

#ifndef MACHO_COMMAND_H_
#define MACHO_COMMAND_H_

#include <libcrippy-1.0/libcrippy.h>

#define	MACHO_CMD_SEGMENT          0x1  // segment of this file to be mapped
#define	MACHO_CMD_SYMTAB           0x2  // link-edit stab symbol table info
#define	MACHO_CMD_SYMSEG           0x3  // link-edit gdb symbol table info (obsolete)
#define	MACHO_CMD_THREAD           0x4  // thread
#define	MACHO_CMD_UNIXTHREAD       0x5  // unix thread (includes a stack)
#define	MACHO_CMD_LOADFVMLIB       0x6  // load a specified fixed VM shared library
#define	MACHO_CMD_IDFVMLIB         0x7  // fixed VM shared library identification
#define	MACHO_CMD_IDENT            0x8  // object identification info (obsolete)
#define MACHO_CMD_FVMFILE          0x9  // fixed VM file inclusion (internal use)
#define MACHO_CMD_PREPAGE          0xA  // prepage command (internal use)
#define	MACHO_CMD_DYSYMTAB         0xB  // dynamic link-edit symbol table info
#define	MACHO_CMD_LOAD_DYLIB       0xC  // load a dynamically linked shared library
#define	MACHO_CMD_ID_DYLIB         0xD  // dynamically linked shared lib ident
#define MACHO_CMD_LOAD_DYLINKER    0xE  // load a dynamic linker
#define MACHO_CMD_ID_DYLINKER      0xF  // dynamic linker identification
#define	MACHO_CMD_PREBOUND_DYLIB   0x10 // modules prebound for a dynamically linked shared library
#define	MACHO_CMD_ROUTINES         0x11 // image routines
#define	MACHO_CMD_SUB_FRAMEWORK    0x12 // sub framework
#define	MACHO_CMD_SUB_UMBRELLA     0x13 // sub umbrella
#define	MACHO_CMD_SUB_CLIENT       0x14 // sub client
#define	MACHO_CMD_SUB_LIBRARY      0x15 // sub library
#define	MACHO_CMD_TWOLEVEL_HINTS   0x16 // two-level namespace lookup hints
#define	MACHO_CMD_PREBIND_CKSUM    0x17 // prebind checksum
//

typedef struct macho_command_info_t_64 {
	uint64_t cmd;
	uint64_t cmdsize;
} macho_command_info_t_64;

typedef struct macho_command_t_64 {
	uint64_t cmd;
	uint64_t size;
	uint64_t index;
	uint64_t offset;
	unsigned char* data;
	macho_command_info_t_64* info;
} macho_command_t_64;


/*
 * Mach-O Command Functions
*/
macho_command_t_64* macho_command_create_64();
macho_command_t_64* macho_command_load_64(unsigned char* data, uint64_t offset);
void macho_command_debug_64(macho_command_t_64* command);
void macho_command_free_64(macho_command_t_64* command);

/*
 * Mach-O Command Info Functions
 */
macho_command_info_t_64* macho_command_info_create_64();
macho_command_info_t_64* macho_command_info_load_64(unsigned char* data, uint64_t offset);
void macho_command_info_debug_64(macho_command_info_t_64* info);
void macho_command_info_free_64(macho_command_info_t_64* info);

#endif /* MACHO_COMMAND_H_ */
