import os
import glob

from pathlib import Path

#files = []
math_funcs = ["cgc_sqrt","cgc_pow", "cgc_log10", "cgc_rint", "cgc_sin", "cgc_cos","cgc_fabs", "cgc_tan", "cgc_log2", "cgc_exp2f", "cgc_sqrtf", "cgc_log2f", "cgc_log", "cgc_atan2", "cgc_remainder"]
path = "../challenges/"
files = [f for f in glob.glob(path + "**/*.c", recursive=True)]

print(files)
for fname in files:
#for fname in Path(path).glob('**/*.c'):
#for fname in os.listdir(path):
	if ".c" in fname:
		f = open(path+fname, "r")
		print("Check ", fname)
		lines = f.readlines()
		#print(lines)
		repl, inc = 0, 0 
		for lno, line in enumerate(lines):
			#print(lno, line)
			for func in math_funcs:
				if func in line:
					line = line.replace(func, func[4:])
					lines[lno] = line
					print("replace ", func, "with ", func[4:], "in ", fname,":", lno)
					repl = 1
		for lno, line in enumerate(lines):
			if repl  and  inc == 0 and "#include" in line:
				lines.insert(lno, "#include <math.h> \n")
				print("put include in", fname,":", lno)
				inc = 1
				break
		f.close()
		fw = open(path+fname, "w")
		#contents = ""
		contents = "".join(lines)
		print(contents)
		fw.write(contents)
		fw.close()

#if __name__== "__main__":
#main()
#findFilese()
