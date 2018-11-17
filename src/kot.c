/*
 * Copyright 2018 Rinwasyu
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
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <dlfcn.h>
#include <dirent.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define VERSION "v0.7.0"
#define DRAW_TITLEBAR_HEIGHT 1
#define DOC_MAXIMUM_ROWS 2000
#define DOC_MAXIMUM_COLS 1000

#include "lib/kbhit.c"
#include "lib/strjoin.c"
#include "editor.c"
#include "doc.c"
#include "cursor.c"
#include "draw.c"
#include "key.c"
#include "plugin.c"

void setup() {
	key.init();
	draw.init();
	doc.init(&doc);
	plugin.init(&plugin);
	atexit(key.exit);
	atexit(draw.clear);
	atexit(draw.exit);
}

int update() {
	if (editor.fit()) {
		draw.repaint(&draw);
	}
	if (kbhit()) {
		key.input(&key);
		draw.repaint(&draw);
	} else {
		if (key.mode == ESC) {
			return 0;
		}
	}
	usleep(1000);
	return 1;
}

int main(int argc, char **argv) {
	setup();
	if (argc == 1) {
		doc.new(&doc, "file.txt");
	} else {
		doc.open(&doc, argv[1]);
	}
	
	while (update()) {}
	
	return 0;
}