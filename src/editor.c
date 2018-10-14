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

struct winsize ws;

struct Editor {
	int col;
	int row;
	int (*fit)();
};

int editor_fit() {
	int b_ws_col = ws.ws_col;
	int b_ws_row = ws.ws_row;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	
	if (ws.ws_col != b_ws_col || ws.ws_row != b_ws_row) {
		return 1;
	}
	return 0;
}

struct Editor editor = {
	0,
	0,
	editor_fit
};