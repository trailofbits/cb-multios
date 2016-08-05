#
# Run from CB root as:
# 	make -f support/dev.mk genpov
#

genpov:
	python poller/for-release/machine.py
