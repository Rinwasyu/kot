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

struct Draw {
	void (*init)();
	void (*exit)();
	void (*clear)();
	void (*titlebar)();
	void (*body)();
	void (*repaint)(struct Draw *);
};

void draw_init() {
	system("stty echo -icanon min 1 time 0");
	system("stty -echo");
	setvbuf(stdout, NULL, _IOFBF, 0);
}

void draw_exit() {
	system("stty sane");
}

void draw_clear() {
	printf("\ec\e[1;1H");
}

void draw_titlebar() {
	printf("\e[1;1H\e[7m kot %s %dx%d row:%d/%d col:%d \e[m\e[m\n", VERSION, ws.ws_col, ws.ws_row, editor.row + cursor.row + 1, doc.rows, editor.col + cursor.col + 1);
}

void draw_body() {
	for (int i = editor.row; i < min(ws.ws_row - DRAW_TITLEBAR_HEIGHT + editor.row, doc.rows); i++) {
		for (int j = editor.col; j < min(ws.ws_col + editor.col, (int)strlen(doc.buf[i]) + editor.col); j++) {
			printf("%c", doc.buf[i][j]);
		}
		if (i != min(ws.ws_row - DRAW_TITLEBAR_HEIGHT + editor.row, doc.rows) - 1) printf("\n");
	}
}

void draw_repaint(struct Draw *draw) {
	draw->clear();
	draw->titlebar();
	draw->body();
	cursor.currentPos(&cursor);
	fflush(stdout);
}

struct Draw draw = {
	draw_init,
	draw_exit,
	draw_clear,
	draw_titlebar,
	draw_body,
	draw_repaint
};