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

struct Cursor {
	int col;
	int row;
	void (*currentPos)(struct Cursor *);
	void (*right)(struct Cursor *);
	void (*left)(struct Cursor *);
	void (*up)(struct Cursor *);
	void (*down)(struct Cursor *);
	void (*home)(struct Cursor *);
	void (*end)(struct Cursor *);
};

void cursor_currentPos(struct Cursor *cursor) {
	printf("\e[%d;%dH", cursor->row + DRAW_TITLEBAR_HEIGHT + 1, cursor->col + 1);
	fflush(stdout);
}

void cursor_right(struct Cursor *cursor) {
	if (cursor->col < strlen(doc.buf[editor.row + cursor->row])) {
		cursor->col++;
	} else {
		if (editor.row + cursor->row < doc.rows-1) {
			cursor->col = 0;
			if (cursor->row == ws.ws_row - DRAW_TITLEBAR_HEIGHT - 1) {
				editor.row++;
			} else {
				cursor->row++;
			}
		}
	}
}

void cursor_left(struct Cursor *cursor) {
	if (cursor->col > 0) {
		cursor->col--;
	} else {
		if (editor.row + cursor->row > 0) {
			if (cursor->row == 0) {
				editor.row--;
			} else {
				cursor->row--;
			}
			cursor->col = strlen(doc.buf[editor.row + cursor->row]);
		}
	}
}

void cursor_up(struct Cursor *cursor) {
	if (editor.row + cursor->row > 0) {
		if (cursor->row == 0) {
			editor.row--;
			if (cursor->col > strlen(doc.buf[editor.row + cursor->row])) {
				cursor->col = strlen(doc.buf[editor.row + cursor->row]);
			}
		} else {
			cursor->row--;
			if (cursor->col > strlen(doc.buf[editor.row + cursor->row])) {
				cursor->col = strlen(doc.buf[editor.row + cursor->row]);
			}
		}
	}
}

void cursor_down(struct Cursor *cursor) {
	if (editor.row + cursor->row < doc.rows - 1) {
		if (cursor->row == ws.ws_row - DRAW_TITLEBAR_HEIGHT - 1) {
			editor.row++;
		} else {
			cursor->row++;
			if (cursor->col > strlen(doc.buf[editor.row + cursor->row])) {
				cursor->col = strlen(doc.buf[editor.row + cursor->row]);
			}
		}
	}
}

void cursor_home(struct Cursor *cursor) {
	cursor->col = strlen(doc.buf[editor.row + cursor->row]);
}

void cursor_end(struct Cursor *cursor) {
	cursor->col = 0;
}

struct Cursor cursor = {
	0,
	0,
	cursor_currentPos,
	cursor_right,
	cursor_left,
	cursor_up,
	cursor_down,
	cursor_home,
	cursor_end
};