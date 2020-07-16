#    Makefile for i3shutdown
#    Copyright (C) 2020  @venji10 <bennisteinir@gmail.com>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.



i3shutdown: i3shutdown.c
	gcc i3shutdown.c -o .i3shutdown `pkg-config --cflags --libs gtk+-3.0`

install: i3shutdown.c
	gcc i3shutdown.c -o .i3shutdown `pkg-config --cflags --libs gtk+-3.0`
	cp .i3shutdown /usr/bin/i3shutdown
