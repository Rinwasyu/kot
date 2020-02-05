/*
 * Copyright 2018,2019,2020 Rinwasyu
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

#include <stdlib.h>

#include "lib/kbhit.c"
#include "cursor.h"
#include "doc.h"
#include "draw.h"
#include "editor.h"
#include "key.h"
#include "kot.h"
#include "option.h"
#include "plugin.h"

void setup() {
	key.init();
	draw.init();
	doc.init(&doc);
	atexit(key.exit);
	atexit(draw.clear);
	atexit(draw.exit);
	plugin.init(&plugin);
}

int update() {
	if (editor.fit()) {
		draw.repaint(&draw);
	}
	if (kbhit()) {
		key.input(&key);
	} else {
		if (key.mode == ESC) {
			return 0;
		}
	}
	usleep(1000);
	return 1;
}

int main(int argc, char **argv) {
	option.readOptions(&option, argc, argv);
	setup();
	if (argc == 1) {
		doc.new(&doc, "file.txt");
	} else {
		doc.open(&doc, argv[1]);
	}
	
	while (update()) {}
	
	return 0;
}
