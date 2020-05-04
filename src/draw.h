/*
 * Copyright 2019,2020 Rinwasyu
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

#ifndef KOT_DRAW_H

#define KOT_DRAW_H

struct Draw {
	void (*init)();
	void (*exit)();
	void (*clear)();
	void (*titlebar)();
	void (*body)();
	void (*prompt)();
	void (*repaint)(struct Draw *);
};

void draw_init();

void draw_exit();

void draw_clear();

void draw_titlebar();

void draw_body();

void draw_prompt();

void draw_repaint(struct Draw *draw);

extern struct Draw draw;

#endif