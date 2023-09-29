/**
 * libmacho-1.0 - segment.h
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

#ifndef MACHO_SEGMENT_H_
#define MACHO_SEGMENT_H_

#include <libmacho-1.0/section.h>
#include <libcrippy-1.0/libcrippy.h>//

typedef struct macho_segment_cmd_t_64 {
	uint64_t cmd;
	uint64_t cmdsize;
	char segname[16];
	uint64_t vmaddr;
	uint64_t vmsize;
	uint64_t fileoff;
	uint64_t filesize;
	uint64_t maxprot;
	uint64_t initprot;
	uint64_t nsects;
	uint64_t flags;
} macho_segment_cmd_t_64;

typedef struct macho_segment_t_64 {
	char* name;
	uint64_t size;
	uint64_t offset;
	uint64_t address;
	unsigned char* data;
	uint64_t section_count;
	macho_section_t_64** sections;
	macho_segment_cmd_t_64* command;
} macho_segment_t_64;

/*
 * Mach-O Segment Functions
 */
macho_segment_t_64* macho_segment_create_64();
macho_segment_t_64* macho_segment_load_64(unsigned char* data, uint64_t offset);
macho_section_t_64* macho_segment_get_section_64(macho_segment_t_64* segment, const char* section);
void macho_segment_debug_64(macho_segment_t_64* segment);
void macho_segment_free_64(macho_segment_t_64* segment);

/*
 * Mach-O Segment Info Functions
 */
macho_segment_cmd_t_64* macho_segment_cmd_create_64();
macho_segment_cmd_t_64* macho_segment_cmd_load_64(unsigned char* data, uint64_t offset);
void macho_segment_cmd_debug_64(macho_segment_cmd_t_64* cmd);
void macho_segment_cmd_free_64(macho_segment_cmd_t_64* cmd);

#endif /* MACHO_SEGMENT_H_ */
