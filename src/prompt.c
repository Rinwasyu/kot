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

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/kbhit.h"
#include "draw.h"
#include "key.h"
#include "kot.h"
#include "prompt.h"

void prompt_init(struct Prompt *prompt) {
	prompt->cursor_col = 0;
	prompt->editor_col = 0;
	prompt->buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	memset(prompt->buf, 0, sizeof(char) * BUFFER_SIZE);
}

void prompt_update(struct Prompt *prompt, char *text) {
	prompt->init(prompt);
	strncpy(prompt->buf, text, sizeof(char) * BUFFER_SIZE);
	prompt->cursor_col = strlen(prompt->buf);
	prompt->active = 1;
	draw.repaint(&draw);
	while (prompt->active) {
		if (kbhit()) {
			key.input(&key);
		} else {
			if (key.mode == ESC) {
				prompt->active = 0;
				key.mode = INSERT;
			}
		}
		usleep(1000);
	}
}

struct Prompt prompt = {
	0, // Not active
	0, // prompt->editor_col
	0, // prompt->cursor_col
	NULL,
	prompt_init,
	prompt_update
};
