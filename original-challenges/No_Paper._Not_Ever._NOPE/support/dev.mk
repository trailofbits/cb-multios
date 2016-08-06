
genpov1c:
	python support/genpov/genpov_1c.py
	pov-xml2c -x support/genpov/POV_1c.povxml -o support/genpov/POV_1c.pov.c
	# /usr/i386-linux-cgc/bin/clang -c -nostdlib -fno-builtin -nostdinc -Iinclude -Ilib -I/usr/include -O0 -g -Werror -Wno-overlength-strings -Wno-packed -o support/genpov/POV_1c.pov.o support/genpov/POV_1c.pov.c
	# /usr/i386-linux-cgc/bin/ld -nostdlib -static -o support/genpov/POV_1c.pov support/genpov/POV_1c.pov.o -L/usr/lib -lcgc -lpov

genpov2c:
	python support/genpov/genpov_2c.py
	pov-xml2c -x support/genpov/POV_2c.povxml -o support/genpov/POV_2c.pov.c

genpov3c:
	python support/genpov/genpov_3c.py
	pov-xml2c -x support/genpov/POV_3c.povxml -o support/genpov/POV_3c.pov.c

# genpov4c:
# 	python support/genpov/genpov_4c.py
# 	pov-xml2c -x support/genpov/POV_4c.povxml -o support/genpov/POV_4c.pov.c

