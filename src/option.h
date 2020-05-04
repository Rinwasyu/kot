/*
 * Copyright 2020 Rinwasyu
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

#ifndef KOT_OPTION_H

#define KOT_OPTION_H

struct Option {
	void (*readOptions)(struct Option *option, int argc, char **argv);
	void (*help)(void);
	void (*version)(void);
};

void option_help(void);
void option_version(void);
void option_readOptions(struct Option *option, int argc, char **argv);

extern struct Option option;

#endif
