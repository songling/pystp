# Copyright notice
# ================
#
# Copyright (C) 2006-2011
#     Lorenzo Martignoni <lorenzo@idea.sec.dico.unimi.it>
#     Roberto Paleari <roberto@idea.sec.dico.unimi.it>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.  
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 51
# Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

.PHONY: all clean

OBJ=pystp.o pystp_stp.o pystp_expr.o pystp_type.o pystp_common.o pystp_list.o
CFLAGS=`python-config --include` -fpic

all: pystp.so

pystp.so: $(OBJ) libstp.so
	$(CXX) -L. $(OBJ) $(CFLAGS) -shared -o $@ -lstp

# Python module
pystp.o: pystp.cc pystp.h pystp_stp.h pystp_expr.h pystp_type.h c_interface.h
	$(CXX) $(CFLAGS) -c pystp.cc

# STP (Stp) Python object
pystp_stp.o: pystp_stp.cc c_interface.h pystp_stp.h pystp_common.h pystp_type.h pystp_expr.h pystp_list.h
	$(CXX) $(CFLAGS) -c pystp_stp.cc

# STP expression (StpExpression) Python object
pystp_expr.o: pystp_expr.cc pystp_expr.h pystp_type.h pystp_stp.h c_interface.h pystp_common.h
	$(CXX) $(CFLAGS) -c pystp_expr.cc

# STP type (StpType) Python object
pystp_type.o: pystp_type.cc pystp_type.h pystp_stp.h c_interface.h pystp_common.h
	$(CXX) $(CFLAGS) -c pystp_type.cc

# common function and macros
pystp_common.o: pystp_common.cc pystp_common.h pystp_stp.h pystp_type.h pystp_expr.h pystp_list.h c_interface.h
	$(CXX) $(CFLAGS) -c pystp_common.cc

# generic list
pystp_list.o: pystp_list.cc pystp_list.h
	$(CXX) $(CFLAGS) -c pystp_list.cc

# transform STP static library in a shared library
libstp.so: libast.a libcinterface.a libconstantbv.a libconsteval.a libminisat.a libsimplifier.a libstp.a
	mkdir tmp_stp ;	cd tmp_stp ; for f in $^ ; do ar -x ../$$f ; done ; $(CXX) -shared -o ../$@ *.o *.or ; cd ..
	rm -fr tmp_stp

# clean up
clean:
	rm $(OBJ)
