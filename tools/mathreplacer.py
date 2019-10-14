import os

#files = []
math_funcs = ["cgc_pow", "cgc_log10", "cgc_rint", "cgc_sin", "cgc_fabs"]
path = "../challenges/ASCII_Content_Server/lib/"

for fname in os.listdir(path):
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
		for line in lines:
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
