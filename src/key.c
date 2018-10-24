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

enum key_Mode {
	INSERT,
	ESC,
	BRACKET
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

void key_init() {
	system("stty stop undef");
	system("stty start undef");
}

void key_exit() {
	system("stty stop ^S");
	system("stty start ^Q");
}

void key_pushbuf(char ch) {
	if (strlen(doc.buf[editor.row + cursor.row]) < DOC_MAXIMUM_COLS) {
		char cpy_ch;
		for (int i = cursor.col; i < strlen(doc.buf[editor.row + cursor.row]) + 1; i++) {
			cpy_ch = doc.buf[editor.row + cursor.row][i];
			doc.buf[editor.row + cursor.row][i] = ch;
			ch = cpy_ch;
		}
	}
}

void key_enter() {
	if (doc.rows < DOC_MAXIMUM_ROWS) {
		char cpy1_buf[DOC_MAXIMUM_COLS];
		strcpy(cpy1_buf, &doc.buf[editor.row + cursor.row][cursor.col]);
		memset(&doc.buf[editor.row + cursor.row][cursor.col], 0, sizeof(char) * DOC_MAXIMUM_COLS);
		for (int i = editor.row + cursor.row + 1; i < doc.rows + 1; i++) {
			char cpy2_buf[DOC_MAXIMUM_COLS] = {0};
			strcpy(cpy2_buf, doc.buf[i]);
			memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
			strcpy(doc.buf[i], cpy1_buf);
			memset(cpy1_buf, 0, sizeof(char) * DOC_MAXIMUM_COLS);
			strcpy(cpy1_buf, cpy2_buf);
		}
		
		doc.rows++;
		cursor.right(&cursor);
	}
}

void key_backspace() {
	if (cursor.col > 0) {
		cursor.left(&cursor);
		for (int i = cursor.col; i < strlen(doc.buf[editor.row + cursor.row]); i++) {
			doc.buf[editor.row + cursor.row][i] = doc.buf[editor.row + cursor.row][i+1];
		}
	} else {
		if (editor.row + cursor.row > 0) {
			cursor.left(&cursor);
			strcpy(&doc.buf[editor.row + cursor.row][strlen(doc.buf[editor.row + cursor.row])], doc.buf[editor.row + cursor.row+1]);
			for (int i = editor.row + cursor.row + 1; i < doc.rows; i++) {
				memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
				strcpy(doc.buf[i], doc.buf[i+1]);
			}
			doc.rows--;
		}
	}
}

void key_delete() {
	if (cursor.col < strlen(doc.buf[editor.row + cursor.row])) {
		for (int i = cursor.col; i < strlen(doc.buf[editor.row + cursor.row]); i++) {
			doc.buf[editor.row + cursor.row][i] = doc.buf[editor.row + cursor.row][i+1];
		}
	} else {
		strcpy(&doc.buf[editor.row + cursor.row][cursor.col], doc.buf[editor.row + cursor.row+1]);
		for (int i = editor.row + cursor.row + 1; i < doc.rows; i++) {
			memset(doc.buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
			strcpy(doc.buf[i], doc.buf[i+1]);
		}
		if (doc.rows > 1) doc.rows--;
	}
}

void key_input(struct Key *key) {
	char ch = getchar();
	
	if (key->mode == INSERT) {
		switch (ch) {
			case 1:	 case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
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
			case 18:
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
			case 91:
				key->mode = BRACKET;
				break;
			default:
				key->mode = INSERT;
				draw.repaint(&draw);
				break;
		}
		return;
	} else if (key->mode == BRACKET) {
		switch (ch) {
			case 65:
				cursor.up(&cursor); break;
			case 66:
				cursor.down(&cursor); break;
			case 67:
				cursor.right(&cursor); break;
			case 68:
				cursor.left(&cursor); break;
			case 70:
				cursor.home(&cursor); break;
			case 72:
				cursor.end(&cursor); break;
			case 126:
				key->delete(); break;
			default:
				return;
		}
		key->mode = INSERT;
		draw.repaint(&draw);
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