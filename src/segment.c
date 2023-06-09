/**
 * libmacho-1.0 - segment.c
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

#include <libmacho-1.0/segment.h>

/*
 * Mach-O Segment Functions
 */
macho_segment_t* macho_segment_create() {
	macho_segment_t* segment = (macho_segment_t*) malloc(sizeof(macho_segment_t));
	if(segment) {
		memset(segment, '\0', sizeof(macho_segment_t));
	}
	return segment;
}

macho_segment_t* macho_segment_load(unsigned char* data, uint64_t offset) {
	unsigned char* address = NULL;
	macho_segment_t* segment = macho_segment_create();
	if (segment) {
		segment->command = macho_segment_cmd_load(data, offset);
		if (!segment->command) {
			macho_segment_free(segment);
			return NULL;
		}
		segment->name = strdup(segment->command->segname);
		segment->size = segment->command->filesize;
		segment->offset = offset;
		segment->address = segment->command->vmaddr;
		segment->data = &data[segment->command->fileoff];
		segment->section_count = segment->command->nsects;
	}
	return segment;
}

macho_section_t* macho_segment_get_section(macho_segment_t* segment, const char* section) {
	int i = 0;
	for(i = 0; i < segment->section_count; i++) {
		macho_section_t* sect = segment->sections[i];
		if(strcmp(sect->name, section) == 0) {
			return sect;
		}
	}
	return NULL;
}

void macho_segment_debug(macho_segment_t* segment) {
	if(segment) {
		debug("\tSegment:\n");
		debug("\t\t   name: %s\n", segment->name);
		debug("\t\t   size: 0x%x\n", segment->size);
		debug("\t\t offset: 0x%x\n", segment->offset);
		debug("\t\taddress: 0x%08x\n", segment->address);
		if(segment->command) {
			macho_segment_cmd_debug(segment->command);
		}
	}
}

void macho_segment_free(macho_segment_t* segment) {
	if (segment) {
		if (segment->command) {
			macho_segment_cmd_free(segment->command);
		}
		if (segment->name) {
			free(segment->name);
		}
		free(segment);
	}
}

/*
 * Mach-O Segment Info Functions
 */
macho_segment_cmd_t* macho_segment_cmd_create() {
	macho_segment_cmd_t* info = malloc(sizeof(macho_segment_cmd_t));
	if (info) {
		memset(info, '\0', sizeof(macho_segment_cmd_t));
	}
	return info;
}

macho_segment_cmd_t* macho_segment_cmd_load(unsigned char* data, uint64_t offset) {
	macho_segment_cmd_t* cmd = macho_segment_cmd_create();
	if (cmd) {
		memcpy(cmd, data+offset, sizeof(macho_segment_cmd_t));
		//macho_segment_cmd_debug(cmd);
	}
	return cmd;
}

void macho_segment_cmd_debug(macho_segment_cmd_t* cmd) {

	if(cmd) {
		debug("\tSegment Command:\n");
		debug("\t\t     cmd = 0x%x\n", cmd->cmd);
		debug("\t\t cmdsize = 0x%x\n", cmd->cmdsize);
		debug("\t\t segname = %s\n", cmd->segname);
		debug("\t\t  vmaddr = 0x%08x\n", cmd->vmaddr);
		debug("\t\t  vmsize = 0x%x\n", cmd->vmsize);
		debug("\t\t fileoff = 0x%x\n", cmd->fileoff);
		debug("\t\tfilesize = 0x%x\n", cmd->filesize);
		debug("\t\t maxprot = 0x%08x\n", cmd->maxprot);
		debug("\t\tinitprot = 0x%08x\n", cmd->initprot);
		debug("\t\t  nsects = 0x%x\n", cmd->nsects);
		debug("\t\t   flags = 0x%08x\n", cmd->flags);
	}

}
void macho_segment_cmd_free(macho_segment_cmd_t* cmd) {
	if (cmd) {
		free(cmd);
	}
}
