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

#include "doc.h"
#include "kot.h"

void doc_init(struct Doc *doc) {
	doc->buf = (char **)malloc(sizeof(char *) * DOC_MAXIMUM_ROWS);
	for (int i = 0; i < DOC_MAXIMUM_ROWS; i++) doc->buf[i] = (char *)malloc(sizeof(char) * DOC_MAXIMUM_COLS);
}

void doc_new(struct Doc *doc, char *file_name) {
	doc->file_name = file_name;
	doc->rows = 1;
}

void doc_open(struct Doc *doc, char *file_name) {
	FILE *fp = fopen(file_name, "r");
	
	if (fp == NULL) {
		doc->new(doc, file_name);
		return;
	}
	
	doc->file_name = file_name;
	
	char f_buf[DOC_MAXIMUM_COLS];
	for (int i = 0; fgets(f_buf, DOC_MAXIMUM_COLS, fp) != NULL && i < DOC_MAXIMUM_ROWS; i++) {
		doc->rows++;
		memset(doc->buf[i], 0, sizeof(char) * DOC_MAXIMUM_COLS);
		if (f_buf[strlen(f_buf) - 1] == '\n') f_buf[strlen(f_buf) - 1] = 0; // Remove '\n'
		strcpy(doc->buf[i], f_buf);
		memset(f_buf, 0, sizeof(char) * DOC_MAXIMUM_COLS);
	}
	
	fclose(fp);
}

void doc_save(struct Doc *doc) {
	FILE *fp = fopen(doc->file_name, "w");
	
	if (fp == NULL) {
		return;
	}
	
	for (int i = 0; i < doc->rows; i++) {
		fputs(doc->buf[i], fp);
		if (i != doc->rows - 1) fputs("\n", fp); // Add '\n'
	}
	
	fclose(fp);
}

void doc_rename(struct Doc *doc, char *file_name) {
	doc->file_name = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	memset(doc->file_name, 0, sizeof(char) * BUFFER_SIZE);
	strncpy(doc->file_name, file_name, BUFFER_SIZE);
}

struct Doc doc = {
	0,
	NULL,
	NULL,
	doc_init,
	doc_new,
	doc_open,
	doc_save,
	doc_rename
};
