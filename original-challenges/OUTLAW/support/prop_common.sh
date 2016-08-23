#!/bin/bash

# Run this from the root CB set folder, e.g. NRFIN_00066.

# copies common files into cb directories
# ./lib and ./include are assumed to the common
# any CB-specific code should be located in cb_X/src
for cbdir in cb_* ; do 
	
	echo "copying into ${cbdir}"

	rm -rf ${cbdir}/lib
	cp -r support/lib ${cbdir}

	rm -rf ${cbdir}/include
	cp -r support/include ${cbdir}
done

