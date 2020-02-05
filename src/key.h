/*
 * Copyright 2019 Rinwasyu
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

#ifndef KOT_KEY_H

#define KOT_KEY_H

enum key_Mode {
	INSERT,
	ESC,
	BRACKET,
	NUMPAD
};

struct Key {
	enum key_Mode mode;
	void (*init)();
	void (*exit)();
	void (*input)(struct Key *key);
	void (*pushbuf)(char);
	void (*enter)();
	void (*backspace)();
	void (*delete)();
};

void key_init();

void key_exit();

void key_pushbuf(char ch);

void key_enter();

void key_backspace();

void key_delete();

void key_input(struct Key *key);

struct Key key;

#endif