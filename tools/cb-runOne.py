from cb_wrapper import runOneAndPrint
from sys import argv


args = len(argv) - 1

if args != 1:
	print("Please provide one argument, the name of the cb. By default, this tests against POV_00000.xml")
	print("Example: $python cb-runOne.py CROMU_00003")

else:
	runOneAndPrint(argv[1], "POV_00000.xml")

