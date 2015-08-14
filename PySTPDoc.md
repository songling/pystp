# What is PySTP? #

PySTP is a Python extension module that interfaces with [STP](http://people.csail.mit.edu/vganesh/stp.html), a decision procedure for the theory of fixed-width bitvectors and arrays. PySTP enables Python scripts to use STP.

# Setup #

PySTP extension module needs to be compiled for the host system where it is going to be used. In order to compile the source, you have to patch STP sources and copy STP static libraries inside PySTP directory.

In detail, follow these steps:
  1. Download STP from [STP Main Page](http://sites.google.com/site/stpfastprover/).
  1. Apply the patch file. Latest PySTP patch is named `20120720-stp-pystp.patch` and has been tested with STP SVN version 1666 (this patch is required because STP includes some undefined external references, that cannot be resolved when the dynamic library is loaded).
  1. Compile STP, running `clean-install.sh`
  1. Copy `lib/libstp.a` to PySTP home directory.
  1. Compile PySTP, running `make` from PySTP home directory.

If everything went well, this will create two shared object files:
  * `pystp.so`; this is PySTP extension module. It must be copied into the default Python module path; otherwise you can copy it anywhere and then tune the environmental variable `PYTHONPATH` accordingly.
  * `libstp.so`; this is STP shared library. You can copy it in a default system library path or you can put it wherever you want and then set the update the environmental variable `LD_LIBRARY_PATH`.

# Copyright #

PySTP is copyrighted by Roberto Paleari and Lorenzo Martignoni.

It is licensed under GPLv3+ (GNU GPL version 3 or later
<http://gnu.org/licenses/gpl.html>). For further information about the license
please read the file COPYING included in the distribution.

# Contact #

Bug reports, patch submissions, and any other useful contribution are very
welcome; just drop an email to:

  * Roberto Paleari <roberto.paleari@gmail.com>
  * Lorenzo Martignoni <martignlo@gmail.com>