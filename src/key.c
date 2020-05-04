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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cursor.h"
#include "doc.h"
#include "draw.h"
#include "editor.h"
#include "key.h"
#include "kot.h"
#include "prompt.h"

void key_init() {
	int errors = 0;
	if (system("stty stop undef") != 0) errors++;
	if (system("stty start undef") != 0) errors++;
	
	if (errors > 0) {
		printf("key_init: error\n");
		exit(-1);
	}
}

void key_exit() {
}

void key_pushbuf(char ch) {
	if (prompt.active == 0) {
		if (strlen(doc.buf[editor.row + cursor.row]) < DOC_MAXIMUM_COLS) {
			char cpy_ch;
			for (int i = editor.col + cursor.col; i < (int)strlen(doc.buf[editor.row + cursor.row]) + 1; i++) {
				cpy_ch = doc.buf[editor.row + cursor.row][i];
				doc.buf[editor.row + cursor.row][i] = ch;
				ch = cpy_ch;
			}
		}
	} else {
		// TODO:
		if (strlen(prompt.buf) < BUFFER_SIZE) {
			char cpy_ch;
			for (int i = prompt.editor_col + prompt.cursor_col; i < (int)strlen(prompt.buf) + 1; i++) {
				cpy_ch = prompt.buf[i];
				prompt.buf[i] = ch;
				ch = cpy_ch;
			}
		}
	}
}

void key_enter() {
	if (prompt.active == 0) {
		if (doc.rows < DOC_MAXIMUM_ROWS) {
			char cpy1_buf[DOC_MAXIMUM_COLS];
			for (int i = editor.row + cursor.row + 1; i < doc.rows + 1; i++) {
				char cpy2_buf[DOC_MAXIMUM_COLS] = {0};
				strcpy(cpy2_buf, doc.buf[i]);
				memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
				strcpy(doc.buf[i], cpy1_buf);
				memset(cpy1_buf, 0, sizeof(char) * DOC_MAXIMUM_COLS);
				strcpy(cpy1_buf, cpy2_buf);
			}
			strcpy(cpy1_buf, &doc.buf[editor.row + cursor.row][editor.col + cursor.col]);
			memset(&doc.buf[editor.row + cursor.row][editor.col + cursor.col], 0, sizeof(char) * (DOC_MAXIMUM_COLS - editor.col - cursor.col + 1));
			strcpy(doc.buf[editor.row + cursor.row + 1], cpy1_buf);
			doc.rows++;
			cursor.right(&cursor);
		}
	} else {
		prompt.active = 0;
	}
}

void key_backspace() {
	if (prompt.active == 0) {
		if (editor.col + cursor.col > 0) {
			cursor.left(&cursor);
			for (int i = editor.col + cursor.col; i < (int)strlen(doc.buf[editor.row + cursor.row]); i++) {
				doc.buf[editor.row + cursor.row][i] = doc.buf[editor.row + cursor.row][i+1];
			}
		} else {
			if (editor.row + cursor.row > 0) {
				cursor.left(&cursor);
				strcpy(&doc.buf[editor.row + cursor.row][strlen(doc.buf[editor.row + cursor.row])], doc.buf[editor.row + cursor.row+1]);
				for (int i = editor.row + cursor.row + 1; i < DOC_MAXIMUM_ROWS - 1; i++) {
					memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
					strcpy(doc.buf[i], doc.buf[i+1]);
					memset(doc.buf[i+1], 0, sizeof(char) * DOC_MAXIMUM_COLS);
				}
				doc.rows--;
			}
		}
	} else {
		if (prompt.editor_col + prompt.cursor_col > 0) {
			cursor.left(&cursor);
			for (int i = prompt.editor_col + prompt.cursor_col; i < (int)strlen(prompt.buf); i++) {
				prompt.buf[i] = prompt.buf[i+1];
			}
		}
	}
}

void key_delete() {
	if (prompt.active == 0) {
		if (editor.col + cursor.col < (int)strlen(doc.buf[editor.row + cursor.row])) {
			for (int i = editor.col + cursor.col; i < (int)strlen(doc.buf[editor.row + cursor.row]); i++) {
				doc.buf[editor.row + cursor.row][i] = doc.buf[editor.row + cursor.row][i+1];
			}
		} else {
			if (doc.rows < DOC_MAXIMUM_ROWS) {
				strcpy(&doc.buf[editor.row + cursor.row][editor.col + cursor.col], doc.buf[editor.row + cursor.row+1]);
			}
			for (int i = editor.row + cursor.row + 1; i < doc.rows && i < DOC_MAXIMUM_ROWS - 1; i++) {
				memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
				strcpy(doc.buf[i], doc.buf[i+1]);
				memset(doc.buf[i+1], 0, sizeof(char) * DOC_MAXIMUM_COLS);
			}
			if (doc.rows > cursor.row + editor.row + 1) doc.rows--;
		}
	} else {
		if (prompt.editor_col + prompt.cursor_col < (int)strlen(prompt.buf)) {
			for (int i = prompt.editor_col + prompt.cursor_col; i < (int)strlen(prompt.buf); i++) {
				prompt.buf[i] = prompt.buf[i+1];
			}
		}
	}
}

void key_input(struct Key *key) {
	char ch = getchar();
	
	if (key->mode == INSERT) {
		switch (ch) {
			case 1:	 case 2: case 3: case 4: case 5: case 6: case 7:
				break;
			case 8:
				key->backspace();
				draw.repaint(&draw);
				break;
			case 9:
				break;
			case 10:	// Enter
				key->enter();
				draw.repaint(&draw);
				break;
			case 11: case 12: case 14: case 15: case 16:
				break;
			case 17:	// Ctrl-q
				exit(0);
				break;
			case 18:	// Ctrl-r
				if (prompt.active == 0) {
					prompt.update(&prompt, "file name", doc.file_name);
					doc.rename(&doc, prompt.buf);
					draw.repaint(&draw);
				}
				break;
			case 19:	// Ctrl-s
				doc.save(&doc);
				break;
			case 20: case 21: case 22: case 23: case 24: case 25: case 26:
				break;
			case 27:	// to ESC mode
				key->mode = ESC;
				break;
			case 127:	// BackSpace
				key->backspace();
				draw.repaint(&draw);
				break;
			default:
				key->pushbuf(ch);
				cursor.right(&cursor);
				draw.repaint(&draw);
				break;
		}
		
		return;
	} else if (key->mode == ESC) {
		switch (ch) {
			case 79: case 91:
				key->mode = BRACKET;
				break;
			default:
				key->mode = INSERT;
				break;
		}
		return;
	} else if (key->mode == BRACKET) {
		switch (ch) {
			case 49:
				key->mode = NUMPAD;
				cursor.home(&cursor);
				return;
			case 52:
				key->mode = NUMPAD;
				cursor.end(&cursor);
				return;
			case 65:
				cursor.up(&cursor); break;
			case 66:
				cursor.down(&cursor); break;
			case 67:
				cursor.right(&cursor); break;
			case 68:
				cursor.left(&cursor); break;
			case 70:
				cursor.end(&cursor); break;
			case 72:
				cursor.home(&cursor); break;
			case 126:
				key->delete(); break;
			default:
				return;
		}
		key->mode = INSERT;
		draw.repaint(&draw);
		return;
	} else if (key->mode == NUMPAD) {
		switch (ch) {
			case 126:
				break;
			default:
				break;
		}
		key->mode = INSERT;
		return;
	}
}

struct Key key = {
	INSERT,
	key_init,
	key_exit,
	key_input,
	key_pushbuf,
	key_enter,
	key_backspace,
	key_delete
};
