files = []
math_funcs = ["cgc_pow", "cgc_log10", "cgc_rint", "cgc_sin", "cgc_fabs"]
path = "../challenges/"

def findFiles():
	for fname in os.listdir(path):
		f = open(path + fname)
		line = f.readline()
		line_no = 1
		while line != '' :
			for func in math_funcs:
				index = line.find(search_str)
				if ( index != -1) :
					files.append(fname)
					 print("added: ", fname, "[", line_no, ":", index, "] ", line)
				line = fo.readline()  
				line_no += 1
		fo.close()


def replaceHeader(f)
	replaced = 0
	for header in headers:
		if header in f:
			f.replace(header, header+"\n #include <math.h> \n")
			replaced = 1
	if replaced == 0:
		for ln in f.readln():
			f.replace(ln, ln+"\n #include <math.h> \n")


def replace():
	for cfile in files:
		f = open(cfile, w)
		replaceHeader(f)
		for func in math_funcs:
			f.replaceAll(func, func[4:]
 

if __name__ == "main":
	findFilese()
	replace()

	
