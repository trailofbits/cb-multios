import struct
import time
import sys
import random
import string

def randString( z ):
	s = ''

	for i in range(z):
		s += random.choice( string.lowercase + string.uppercase + string.digits)

	return s

def delfile( dirs ):
	### randomly select a directory then pull the file to remove
	fl = ''
	cnt = 0

	while fl == '' and cnt < 30:
		z = random.choice(dirs)

		cnt += 1

		if len(z[1]) == 0:
			continue

		f = random.choice(z[1])
		i = z[1].index(f)
		del z[1][i]

		fl = f[0]
		
	if fl == '':
		return ''

	data = '\t\t<write echo="ascii"><data>REPO\\x%.2x%s</data></write>\n' %(len(fl), fl)

	i = fl.rfind('/')
	fl = fl[i+1:]
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[INFO] %s removed\\n</data></match></read>\n' %(fl)

	return data

def addfile( dirs ):
	### Select a base dir to add the file
	td = random.choice( dirs )

	base_dir = td[0]
	
	maxlen = 10

	if (254 - len(base_dir)) < 10:
		return ''

	n = randString( random.randint(4, 10) )

	newfile = base_dir + '/' + n
	fdata = randString( random.randint(20,100) )

	z = 'SEND\\x%.2x%s' %(len(newfile), newfile) 
	z += '\\x%.2x\\x%.2x%s' %( len(fdata)&0xff, (len(fdata)>>8)&0xff, fdata )

	data = '\t\t<write echo="ascii"><data>%s</data></write>\n' %(z)
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[INFO] File received: %s\\n</data></match></read>\n' %(newfile)

	td[1].append( [newfile, fdata] )

	return data

def getFile( dirs ):
	### Select a base dir with a file

	t = []
	cnt = 0

	while t == [] and cnt < 30:
		z = random.choice( dirs )
		if len(z[1]) != 1:
			t = z[1]
			break
		cnt += 1

	if t == []:
		return ''

	fl = random.choice(t)

	req = 'RECV\\x%.2x%s' %( len(fl[0]), fl[0] )

	data = '\t\t<write echo="ascii"><data>%s</data></write>\n' %(req)
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[DATA] %s\\n</data></match></read>\n' %(fl[1])

	return data

def addDir( dirs ):
	### Select a base dir to add
	td = random.choice( dirs )

	base_dir = td[0]
	
	maxlen = 10

	if (254 - len(base_dir)) < 10:
		return ''

	n = randString( random.randint(4, 10) )

	newdir = base_dir + '/' + n

	z = 'NDIR\\x%.2x%s' %(len(newdir), newdir) 

	data = '\t\t<write echo="ascii"><data>' + z + '</data></write>\n'
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[INFO] Added new directory\\n</data></match></read>\n'

	dirs.append( [ newdir, [] ] )

	return data

def addPrint( dirs ):

	c = []
	for x in dirs:
		for y in x[1]:
			c.append( [ y[0], 'File', str(len(y[1]))] )

		if x[0] == '':
			continue

		c.append( [x[0], 'Dir', '' ])

	c.sort(key=lambda x: x[0])

	data = '\t\t<write echo="ascii"><data>PRNT</data></write>\n'
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[INFO] Listing files\\n</data></match></read>\n'

	for y in c:
		if y[1] == 'File':
			l = '     ' + y[2]
		else:
			l = ''

		data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>%s     %s%s\\n</data></match></read>\n' %(y[0], y[1], l)


	return data

def addStop():
	data = '\t\t<write echo="ascii"><data>STOP</data></write>\n'
	data += '\t\t<read echo="ascii"><delim>\\n</delim><match><data>[INFO] Terminating\\n</data></match></read>\n'

	return data

def newpoll( ind ):
	dir_structure = [ ['', [] ] ]

	data = '<?xml version="1.0" standalone="no" ?>\n'
	data += '<!DOCTYPE pov SYSTEM "/usr/share/cgc-replay/replay.dtd">\n'
	data += '<pov>\n'
	data += '\t<cbid>CROMU_00033</cbid>\n'
	data += '\t<replay>\n'

	flist = [addDir, addfile, getFile]
	repo = 0

	for i in range(0, random.randint(105, 200)):
		if i == 100:
			flist.append(delfile)

		b = random.choice( flist )
		if b == delfile:
			repo = 1

		data += b( dir_structure )

	### Only add this in if a file has been not been deleted
	if repo == 0:
		data += addPrint( dir_structure )

	data += addStop()

	data += '\t</replay>\n'
	data += '</pov>\n'

	f = open("./poller/for-testing/POLL%.5d.xml" %(ind), "wb")
	f.write(data)
	f.close()

if __name__ == '__main__':
	seed = time.time()

	if len(sys.argv) == 2:
		seed = int(sys.argv[1])

	random.seed(seed)

	for i in range(1, 1000):
		newpoll(i)
