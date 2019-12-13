#
# Copyright 2019 Rinwasyu
# 
# This file is part of kot.
# 
# Kot is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Kot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
# 

.PHONY: all clean

PROGNAME	:= kot
CC			:= gcc
CFLAGS		:= -O2 -Wall -W
LDFLAGS		:= 
SRCS		:= $(wildcard *.c)
OBJS		:= $(SRCS:%.c=%.o)
DEPS		:= $(SRCS:%.c=%.d)

all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -MD -c $<

clean:
	rm -rf *.o *.d

-include $(DEPS)
