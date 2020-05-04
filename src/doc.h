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

#ifndef KOT_DOC_H

#define KOT_DOC_H

struct Doc {
	int rows;
	char **buf;
	char *file_name;
	void (*init)(struct Doc *);
	void (*new)(struct Doc *, char *);
	void (*open)(struct Doc *, char *);
	void (*save)(struct Doc *);
	void (*rename)(struct Doc *, char *file_name);
};

void doc_init(struct Doc *doc);

void doc_new(struct Doc *doc, char *file_name);

void doc_open(struct Doc *doc, char *file_name);

void doc_save(struct Doc *doc);

void doc_rename(struct Doc *doc, char *file_name);

extern struct Doc doc;

#endif