/*
 * Copyright 2020 Rinwasyu
 * 
 * This file is part of kot.
 * 
 * Kot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Kot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kot.h"
#include "option.h"

void option_help() {
	printf("Usage: %s [--help] [--version]\n", KOT_PROGNAME);
	exit(0);
}

void option_version() {
	printf("%s %s\n", KOT_PROGNAME, KOT_VERSION);
	printf("Copyright %s %s\n", KOT_AUTHOR_YEAR, KOT_AUTHOR);
	printf("%s\n", KOT_WEBSITE);
	printf("This program is licensed under %s\n", KOT_LICENSE);
	exit(0);
}

void option_readOptions(struct Option *option, int argc, char **argv) {
	int unknown_options = 0;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			int j = 1;
			for (; argv[i][j] == '-'; j++);
			
			if (strcmp(&argv[i][j], "help") == 0) {
				option->help();
			} else if (strcmp(&argv[i][j], "version") == 0) {
				option->version();
			} else {
				printf("Unknown option: %s\n", argv[i]);
				unknown_options++;
			}
		}
	}
	if (unknown_options > 0) {
		option->help();
	}
}

struct Option option = {
	option_readOptions,
	option_help,
	option_version
};
