import os

#files = []
math_funcs = ["cgc_pow", "cgc_log10", "cgc_rint", "cgc_sin", "cgc_fabs"]










path = "../challenges/ASCII_Content_Server/lib/"

#def main(): 
#	findFiles()
#	return

for fname in os.listdir(path):
	if ".c" in fname:
		f = open(path + fname, "rw")
		print("Check ", fname)
		line = f.readline()
		replaced = 0
		line_no = 1
		while line != '' :
			if "#include" in line and replaced == 0:
				f.write(line.replace(line, "\n #include <math.h> \n"+line))
				replaced = 1
				print("put include in", fname,":", lno)
			for func in math_funcs:
				index = line.find(func)
				if ( index != -1) :
					f.write(line.replace(func, func[4:]))
					print("replace ", func, "with ", func[4:], "in ", fname,":", lno)
				line = f.readline()  
				line_no += 1
		if replaced == 0:
			print("Odd, this file doesnt include anything?")
		f.close()


#def replaceHeader(f):
#	replaced = 0
#	for header in headers:
#		if header in f:
#			f.replace(header, header+"\n #include <math.h> \n")
#			replaced = 1
#	if replaced == 0:
#		for ln in f.readln():
#			f.replace(ln, ln+"\n #include <math.h> \n")


#def replace():
#	for fname in os.listdir(path):
#		f = open(path+fname, "w")
#		
#		replaceHeader(f)
#		for func in math_funcs:
#			f.replaceAll(func, func[4:]

#if __name__== "__main__":
#main()
#findFilese()
