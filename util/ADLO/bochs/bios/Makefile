# Copyright (C) 2001  MandrakeSoft S.A.
#
#   MandrakeSoft S.A.
#   43, rue d'Aboukir
#   75002 Paris - France
#   http://www.linux-mandrake.com/
#   http://www.mandrakesoft.com/
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

# Makefile for the BIOS component of bochs

.SUFFIXES: .cc

# -------- end configurable options --------------------------

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(LOCAL_CXXFLAGS) $(BX_INCDIRS) $< -o $@

bios: rombios.bin

rombios.bin: rombios.c
	gcc -E $< > _rombios_.c
	bcc -o rombios.s -C-c -D__i86__ -0 -S _rombios_.c
	sed -e 's/^\.text//' -e 's/^\.data//' rombios.s > _rombios_.s
	as86 _rombios_.s -b rombios.bin -u- -w- -g -0 -j -O -l rombios.txt
	ls -l rombios.bin

# -----------------------------------------------------------------

clean:
	rm -f  *.s
	rm -f  _rombios_.c
	rm -f  rombios.txt

biosclean:
	rm -f  rombios.bin

distclean: clean biosclean

# -----------------------------------------------------------------

diff:
	( diff -Bbwiu ../bochs-cvs/bochs/bios/rombios.c rombios.c ; true )

# -----------------------------------------------------------------
