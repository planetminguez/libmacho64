/**
 * libmacho-1.0 - macho.h
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

#ifndef MACHO_H_
#define MACHO_H_

#include <libcrippy-1.0/debug.h>
#include <libcrippy-1.0/libcrippy.h>

#include "libmacho-1.0/symtab.h"
#include "libmacho-1.0/segment.h"
#include "libmacho-1.0/section.h"
#include "libmacho-1.0/command.h"

#define MACHO_MAGIC_32  0xFEEDFACE
#define MACHO_MAGIC_64  0xFEEDFACF
#define MACHO_MAGIC_FAT 0xCAFEBABE// 

typedef struct macho_header_t_64 {
	uint64_t magic;
	uint64_t cputype;
	uint64_t cpusubtype;
	uint64_t filetype;
	uint64_t ncmds;
	uint64_t sizeofcmds;
	uint64_t flags;
} macho_header_t_64;

typedef struct macho_t_64 { 
	uint16_t* data;
	uint64_t size;
	uint64_t offset;
	uint64_t command_count;
	uint64_t segment_count;
	uint64_t symtab_count;
	macho_header_t_64* header;
	macho_symtab_t_64** symtabs;
	macho_command_t_64** commands;
	macho_segment_t_64** segments;
} macho_t_64;

/*
 * Mach-O Functions
 */
macho_t_64* macho_create_64();
macho_t_64* macho_open_64(const char* path);
macho_t_64* macho_load_64(unsigned char* data, uint64_t size);
void macho_debug_64(macho_t_64* macho);
void macho_free_64(macho_t_64* macho);

uint64_t macho_lookup_64(macho_t_64* macho, const char* sym);
macho_segment_t_64* macho_get_segment_64(macho_t_64* macho, const char* segment);
macho_section_t_64* macho_get_section_64(macho_t_64* macho, const char* segment, const char* section);
void macho_list_symbols_64(macho_t_64* macho, void (*print_func)(const char*, uint64_t, void*), void* userdata);


int macho_handle_command_64(macho_t_64* macho, macho_command_t_64* command);

/*
 * Mach-O Header Functions
 */
macho_header_t_64* macho_header_create_64();
macho_header_t_64* macho_header_load_64(macho_t_64* macho);
void macho_header_debug_64(macho_t_64* macho);
void macho_header_free_64(macho_header_t_64* header);

/*
 * Mach-O Commands Functions
 */
macho_command_t_64** macho_commands_create_64(uint64_t count);
macho_command_t_64** macho_commands_load_64(macho_t_64* macho);
void macho_commands_debug_64(macho_t_64* macho);
void macho_commands_free_64(macho_command_t_64** commands);

/*
 * Mach-O Segments Functions
 */
macho_segment_t_64** macho_segments_create_64(uint64_t count);
macho_segment_t_64** macho_segments_load_64(macho_t_64* macho);
void macho_segments_debug_64(macho_t_64* macho);
void macho_segments_free_64(macho_segment_t_64** segments);

/*
 * Mach-O Symtab Functions
 */
macho_symtab_t_64** macho_symtabs_create_64(uint64_t count);
macho_symtab_t_64** macho_symtabs_load_64(macho_t_64* macho);
void macho_symtabs_debug_64(macho_t_64* macho);
void macho_symtabs_free_64(macho_symtab_t_64** symtabs);

/*
 * Mach-O Sections Functions
 */
macho_section_t_64** macho_sections_create_64(uint64_t count);
macho_section_t_64** macho_sections_load_64(macho_t_64* macho, macho_segment_t_64* segment);
void macho_sections_debug_64(macho_section_t_64** sections);
void macho_sections_free_64(macho_section_t_64** sections);

#endif /* MACHO_H_ */
