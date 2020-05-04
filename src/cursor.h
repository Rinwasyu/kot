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

#ifndef KOT_CURSOR_H

#define KOT_CURSOR_H

struct Cursor {
	int col;
	int row;
	void (*currentPos)(struct Cursor *);
	void (*right)(struct Cursor *);
	void (*left)(struct Cursor *);
	void (*up)(struct Cursor *);
	void (*down)(struct Cursor *);
	void (*end)(struct Cursor *);
	void (*home)(struct Cursor *);
};

void cursor_currentPos(struct Cursor *cursor);

void cursor_right(struct Cursor *cursor);

void cursor_left(struct Cursor *cursor);

void cursor_up(struct Cursor *cursor);

void cursor_down(struct Cursor *cursor);

void cursor_end(struct Cursor *cursor);

void cursor_home(struct Cursor *cursor);

extern struct Cursor cursor;

#endif