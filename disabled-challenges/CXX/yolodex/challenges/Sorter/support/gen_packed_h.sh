#!/bin/bash

#cd ..
# Create Unpatched Disassembly
rm -rf gdb.txt
sed -i 's/\-O2/\-O0/' Makefile
mv src/service.c src/service_c
mv support/service_unpacked_unpatched_c src/service_unpacked_unpatched.c
make release
gdb build/release/bin/KPRCA_00088 -x support/gdb_disas_cmds
mv src/service_unpacked_unpatched.c support/service_unpacked_unpatched_c
mv support/service_unpacked_patched_c src/service_unpacked_patched.c
mv gdb.txt support/gdb.txt
make clean
make release
gdb build/release/bin/KPRCA_00088 -x support/gdb_disas_cmds2
mv src/service_unpacked_patched.c support/service_unpacked_patched_c
mv src/service_c src/service.c
mv gdb.txt support/gdb2.txt
sed -i 's/\-O0/\-O2/' Makefile
make clean
#Done Created Unpatched assembly

#Generate the packed.h file
cd support
python parse_gdb.py
rm -rf gdb.txt
rm -rf gdb2.txt
#done

