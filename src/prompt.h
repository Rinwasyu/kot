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

#ifndef KOT_PROMPT_H

#define KOT_PROMPT_H

struct Prompt {
	int active;
	int editor_col;
	int cursor_col;
	char *buf;
	void (*init)(struct Prompt *);
	void (*update)(struct Prompt *, char *);
};

void prompt_init(struct Prompt *prompt);
void prompt_update(struct Prompt *prompt, char *text);

struct Prompt prompt;

#endif
