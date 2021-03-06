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
#include <string.h>

#include "cursor.h"
#include "doc.h"
#include "editor.h"
#include "kot.h"
#include "prompt.h"

void cursor_currentPos(struct Cursor *cursor) {
	if (prompt.active == 0) {
		printf("\e[%d;%dH", cursor->row + DRAW_TITLEBAR_HEIGHT + 1, cursor->col + 1);
	} else {
		printf("\e[2;%dH", prompt.cursor_col + 1 + PROMPT_DISCR_LENGTH);
	}
	fflush(stdout);
}

void cursor_right(struct Cursor *cursor) {
	if (prompt.active == 0) {
		if (editor.col + cursor->col < (int)strlen(doc.buf[editor.row + cursor->row])) {
			if (cursor->col == ws.ws_col - 1) {
				editor.col++;
			} else {
				cursor->col++;
			}
		} else {
			if (editor.row + cursor->row < doc.rows-1) {
				editor.col = 0;
				cursor->col = 0;
				if (cursor->row == ws.ws_row - DRAW_TITLEBAR_HEIGHT - 1) {
					editor.row++;
				} else {
					cursor->row++;
				}
			}
		}
	} else {
		if (prompt.editor_col + prompt.cursor_col < (int)strlen(prompt.buf)) {
			if (prompt.cursor_col == ws.ws_col - 1 - PROMPT_DISCR_LENGTH) {
				prompt.editor_col++;
			} else {
				prompt.cursor_col++;
			}
		}
	}
}

void cursor_left(struct Cursor *cursor) {
	if (prompt.active == 0) {
		if (editor.col + cursor->col > 0) {
			if (cursor->col == 0) {
				if (editor.col > 0) {
					editor.col--;
				}
			} else {
				cursor->col--;
			}
		} else {
			if (editor.row + cursor->row > 0) {
				if (cursor->row == 0) {
					editor.row--;
				} else {
					cursor->row--;
				}
				editor.col = max(0, (int)strlen(doc.buf[editor.row + cursor->row]) - ws.ws_col + 1);
				cursor->col = min((int)strlen(doc.buf[editor.row + cursor->row]),  ws.ws_col - 1);
			}
		}
	} else {
		if (prompt.editor_col + prompt.cursor_col > 0) {
			if (prompt.cursor_col == 0) {
				if (prompt.editor_col > 0) {
					prompt.editor_col--;
				}
			} else {
				prompt.cursor_col--;
			}
		}
	}
}

void cursor_up(struct Cursor *cursor) {
	if (prompt.active == 0) {
		if (editor.row + cursor->row > 0) {
			if (cursor->row == 0) {
				editor.row--;
				if (editor.col + cursor->col > (int)strlen(doc.buf[editor.row + cursor->row])) {
					editor.col = max(0, (int)strlen(doc.buf[editor.row + cursor->row]) - ws.ws_col + 1);
					cursor->col = min((int)strlen(doc.buf[editor.row + cursor->row]),  ws.ws_col - 1);
				}
			} else {
				cursor->row--;
				if (editor.col + cursor->col > (int)strlen(doc.buf[editor.row + cursor->row])) {
					if (editor.col < (int)strlen(doc.buf[editor.row + cursor->row])) {
						cursor->col = (int)strlen(doc.buf[editor.row + cursor->row]) - editor.col;
					} else {
						editor.col = (int)strlen(doc.buf[editor.row + cursor->row]);
						cursor->col = 0;
					}
				}
			}
		}
	}
}

void cursor_down(struct Cursor *cursor) {
	if (prompt.active == 0) {
		if (editor.row + cursor->row < doc.rows - 1) {
			if (cursor->row == ws.ws_row - DRAW_TITLEBAR_HEIGHT - 1) {
				editor.row++;
			} else {
				cursor->row++;
				if (editor.col + cursor->col > (int)strlen(doc.buf[editor.row + cursor->row])) {
					if (editor.col < (int)strlen(doc.buf[editor.row + cursor->row])) {
						cursor->col = (int)strlen(doc.buf[editor.row + cursor->row]) - editor.col;
					} else {
						editor.col = (int)strlen(doc.buf[editor.row + cursor->row]);
						cursor->col = 0;
					}
				}
			}
		}
	}
}

void cursor_end(struct Cursor *cursor) {
	if (prompt.active == 0) {
		if (editor.col + ws.ws_col - (int)strlen(doc.buf[editor.row + cursor->row]) >= 0) {
			cursor->col = (int)strlen(doc.buf[editor.row + cursor->row]) - editor.col;
		} else {
			editor.col = (int)strlen(doc.buf[editor.row + cursor->row]) - ws.ws_col + 1;
			cursor->col = ws.ws_col - 1;
		}
	} else {
		if (prompt.editor_col + ws.ws_col - PROMPT_DISCR_LENGTH - (int)strlen(prompt.buf) >= 0) {
			prompt.cursor_col = (int)strlen(prompt.buf) - prompt.editor_col;
		} else {
			prompt.editor_col = (int)strlen(prompt.buf) - ws.ws_col + 1 + PROMPT_DISCR_LENGTH;
			prompt.cursor_col = ws.ws_col - 1 - PROMPT_DISCR_LENGTH;
		}
	}
}

void cursor_home(struct Cursor *cursor) {
	if (prompt.active == 0) {
		editor.col = 0;
		cursor->col = 0;
	} else {
		prompt.editor_col = 0;
		prompt.cursor_col = 0;
	}
}

struct Cursor cursor = {
	0,
	0,
	cursor_currentPos,
	cursor_right,
	cursor_left,
	cursor_up,
	cursor_down,
	cursor_end,
	cursor_home
};
