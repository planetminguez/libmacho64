/**
 * libmacho-1.0 - symbol.h
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

#ifndef MACHO_SYMBOL_H_
#define MACHO_SYMBOL_H_

typedef struct macho_header_t_64 {
	uint64_t magic;
} macho_symbol_info_t_64;

typedef struct macho_symbol_t_64 {
	macho_symbol_info_t_64* info;
} macho_symbol_t_64;

/*
 * Mach-O Segment Functions
 */
macho_symbol_t_64* macho_symbol_create_64();
macho_symbol_t_64* macho_symbol_load_64(unsigned char* data, uint64_t offset);
void macho_symbol_debug_64(macho_symbol_t_64* command);
void macho_symbol_free_64(macho_symbol_t_64* command);

/*
 * Mach-O Segment Info Functions
 */
macho_symbol_info_t_64* macho_symbol_info_create_64();
macho_symbol_info_t_64* macho_symbol_info_load_64(unsigned char* data, uint64_t offset);
void macho_symbol_info_debug_64(macho_symbol_info_t_64* info);
void macho_symbol_info_free_64(macho_symbol_info_t_64* info);

#endif /* MACHO_SYMBOL_H_ */
