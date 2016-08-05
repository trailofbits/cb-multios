from generator.actions import Actions
import random

import os
import subprocess
import re

objdump_path = "/usr/i386-linux-cgc/bin/objdump"
objdump_options = ["-d", "--insn-width=20"] #we use a long insn width so we can figure out the length of the insn
objdump_header_options = ["-h"]
dump_ext = ".dump"

bin_path = "bin"
build_path = "build"

cb = "YAN01_00016"
cb_path = os.path.join(bin_path, cb)
cb_dump_path = os.path.join(build_path, cb + dump_ext)

patched_path = os.path.join(bin_path, cb + "_patched")
patched_dump_path = os.path.join(build_path, cb + "_patched" + dump_ext)

def getDumps(inFile_path, outFile_path, dumpCmd_path, dumpCmd_options, bForce = False) :
  if bForce or not os.path.exists(outFile_path) :
    outFile = open(outFile_path, "w")
    ret = 0
    try :
      ret = subprocess.call([dumpCmd_path] + dumpCmd_options + [inFile_path], stdout=outFile)
    except OSError :
      ret = -1
    
    outFile.close()
    if ret != 0 :
      os.remove(outFile_path)
  
def getObjdumps(bForce = False) :
  getDumps(cb_path, cb_dump_path, objdump_path, objdump_options, bForce) 
  getDumps(patched_path, patched_dump_path, objdump_path, objdump_options, bForce) 

header_ext = ".header"
cb_header_path = os.path.join(build_path, cb + header_ext)
patched_header_path = os.path.join(build_path, cb + "_patched" + header_ext)

def getObjdumpHeaders(bForce = False) :
  getDumps(cb_path, cb_header_path, objdump_path, objdump_header_options, bForce)
  getDumps(patched_path, patched_header_path, objdump_path, objdump_header_options, bForce)

diff_ext = ".diff"
diffFile_path = os.path.join(build_path, cb + diff_ext)
  
def getDiffFile(bForce = False) :
  if os.path.exists(diffFile_path) and not bForce:
    return

  if not os.path.exists(cb_dump_path) or not os.path.exists(patched_dump_path) or bForce:
    getObjdumps(bForce)

  assert os.path.exists(cb_dump_path) and os.path.exists(patched_dump_path)

  outFile = open(diffFile_path, "w")
  ret = 0
  try :
    ret = subprocess.call(["/usr/bin/diff", cb_dump_path, patched_dump_path], stdout=outFile)
  except OSError :
    ret = -1 

  outFile.close()
  #if ret != 0 :
  if ret != 1 : #seems like diff returns 1 on success?????
    os.remove(diffFile_path)
     
offsets_ext = ".off"
offsets_path = os.path.join(build_path, cb + offsets_ext)
 
def processDiffToOffsets(out_path, df_path, getDiffFunc, bForce = False) :
  if os.path.exists(out_path) and not bForce :
    return #nothing to do

  if not os.path.exists(df_path) or bForce:
    getDiffFunc(bForce)

  assert os.path.exists(df_path)

  #now that we have the diff file, lets just process it
  outFile = open(out_path, "w")
  for l in open(df_path) :
    mat = re.match("[\<\>]\s+([0-9a-fA-F]+):\s+([0-9a-fA-F ]+)\t", l)
    if mat :
      #print "MATCH: " + l
      outFile.write(mat.group(1) + ':' + mat.group(2) + '\n')
    else :
      #print "NO MATCH: " + l
      pass

  outFile.close()

hexdump_path = "hexdump"
hexdump_options = ['-e', '" %08_ax:" 16/1 " %02x""\t\n"'] #address then colon then the raw bytes -similar to objdump output (notice the \t)
hd_diff_ext = ".hddiff"
hd_ext = ".hexdump"
hd_offsets_ext = ".hdoff"
hd_offsets_path = os.path.join(build_path, cb + hd_offsets_ext)
hd_diffFile_path = os.path.join(build_path, cb + hd_diff_ext)
cb_hd_path = os.path.join(build_path, cb + hd_ext)
patched_hd_path = os.path.join(build_path, cb + "_patched" + hd_ext)

def getHexdumps(bForce = False) :
  getDumps(cb_path, cb_hd_path, hexdump_path, hexdump_options, bForce)
  getDumps(patched_path, patched_hd_path, hexdump_path, hexdump_options, bForce)

def getHDDiffFile(bForce = False) :
  if os.path.exists(hd_diffFile_path) and not bForce :
    return

  if not os.path.exists(cb_hd_path) or not os.path.exists(patched_hd_path) or bForce :
    getHexdumps(bForce)
  
  assert os.path.exists(cb_hd_path) and os.path.exists(patched_hd_path) 

  outFile = open(hd_diffFile_path, "w")
  ret = 0
  try :
    ret = subprocess.call(["/usr/bin/diff", cb_hd_path, patched_hd_path], stdout=outFile)
  except OSError :
    ret = -1 

  outFile.close()
  #if ret != 0 :
  if ret != 1 : #seems like diff returns 1 on success?????
    os.remove(hd_diffFile_path)

def loadOffsets(off_path, diff_path, getDiffFunc, bForce = False) :
  processDiffToOffsets(off_path, diff_path, getDiffFunc, bForce)
  try :
    if os.path.getsize(off_path) == 0 : #there MUST be differences
      processDiffToOffsets(off_path, diff_path, getDiffFunc, True)
  except OSError : #we get an OSError if the file doesn't exist
    pass #nothing to do because we will check on the file afterwards

  assert os.path.exists(off_path)

  ret = {}
  #now that we have the offsets file, just read it into a dict and return
  i = 1
  for l in open(off_path) :    
    elems = l.split(':')
    if len(elems) != 2 :
      print "WARNING: Can't Process this line @ %u [%s]" % (i, l)
    else :
      k = elems[0]
      v = len("".join(elems[1].split())) / 2

      if k not in ret :
        ret[k] = v
      else :
        if v > ret[k] :
          ret[k] = v
 
    i += 1 

  return ret

def loadObjdumpOffsets(bForce = False) :
  return loadOffsets(offsets_path, diffFile_path, getDiffFile, bForce)

def loadHexdumpOffsets(bForce = False) :
  return loadOffsets(hd_offsets_path, hd_diffFile_path, getHDDiffFile, bForce)

def getHexdumpDifferences(bForce = False) :
  processDiffToOffsets(hd_offsets_path, hd_diffFile_path, getHDDiffFile, bForce)
  try :
    if os.path.getsize(hd_offsets_path) == 0 : #there MUST be differences
      processDiffToOffsets(hd_offsets_path, hd_diffFile_path, getHDDiffFile, True)
  except OSError : #we get an OSError if the file doesn't exist
    pass #nothing to do because we will check on the file afterwards

  assert os.path.exists(hd_offsets_path)

  ret = {}
  curOffsets = {}
  #now that we have the offsets file, just read it into a dict and return
  i = 1
  for l in open(hd_offsets_path) :    
    elems = l.split(':')
    if len(elems) != 2 :
      print "WARNING: Can't Process this line @ %u [%s]" % (i, l)
    else :
      k = elems[0]
      v = elems[1]
 
      if k not in curOffsets :
        curOffsets[k] = v
      else : #since it already exists, lets go through the values to see which bytes are different
        ki = int(k,16) #let this except and die if necessary 
        va = v.split()
  
        ca = curOffsets[k].split()

        assert len(va) == len(ca) #both should be 16 bytes...? what if its at the end? - will handle it later perhaps

        j = 0
        bCurDiff = False
        baseAddr = ki
        endAddr = ki
        while j < len(va) :
          if va[j] != ca[j] :
            if bCurDiff :
              #if they are still different then update the end Addr
              #endAddr += 1 #already done automatically
              pass
            else :
              #if they are different, but didn't used to be then update the base addr and set the flag
              baseAddr = ki + j

            bCurDiff = True
          else :
            #now if they are the same
            if bCurDiff :
              #if they used to be different, then that means we have new range so add to ret
              ret[baseAddr] = endAddr - baseAddr
              baseAddr = endAddr
            else :
              #if they used to be the same, then just update the base addr
              baseAddr += 1
            bCurDiff = False

          j += 1
          endAddr += 1

        #if we are all the way here then we need to make sure that there wasn't some difference
        # we missed at the end of the line
        if bCurDiff :
          ret[baseAddr] = endAddr - baseAddr
           
    i += 1 

  return ret

def parseHeaderOffsets(filename) :
  temp = {}

  for l in open(filename) :
    mat = re.match("\s+\d+\s+(.[\w]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+[0-9a-fA-F]+\s+([0-9a-fA-F]+)", l)
    if mat :
      if mat.group(1) in temp :
        print "WARNING: Somehow the section [%s] already exists?" % mat.group(1)
      #try :
      temp[mat.group(1)] = (int(mat.group(2),16), int(mat.group(3),16), int(mat.group(4),16))
      #except ValueError : I want the exception to stop things
    else :
      pass
      
  return temp

def loadObjdumpHeaderOffsets(bForce = False) :
  getObjdumpHeaders(bForce)
 
  try :
    if os.path.getsize(cb_header_path) == 0 or os.path.getsize(patched_header_path) == 0 :
      assert False 
  except OSError :
    assert False

  header1 = parseHeaderOffsets(cb_header_path)
  header2 = parseHeaderOffsets(patched_header_path)

  return header1, header2

'''
objOffsets = loadObjdumpOffsets()
hexOffsets = loadHexdumpOffsets()
print objOffsets
print hexOffsets

h1, h2 = loadObjdumpHeaderOffsets()
print h1
print h2
print getHexdumpDifferences()
'''
#now that we have the dumps (or should have the dumps) we can do a diff


HASH_SIZE = 128
MAX_PCRS = 8

MAX_HASH_TEST = 4096
pcrNums = range(MAX_PCRS)

toHexStr = [ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' ]

MAGIC_PAGE = 0x4347C000

class TPM(Actions):

  def hashToStr(self, h) :
    s = ""
    for _ in h:
      high = (_ >> 4) & 0xF 
      low = _ & 0xF
      s += toHexStr[high]
      s += toHexStr[low]
  
    return s
  
  def xorhash(self, dataIn, hashOut) :
    i = 0
    for _ in dataIn :
      temp = _ ^ hashOut[i]
      hashOut[i] = temp
      i += 1
      if (i == HASH_SIZE) :
        i = 0 
  
  def extendHash(self, pcr, fileoff, numBytes) :
    f = open(cb_path, "rb")
    f.seek(fileoff)
    tempdata = f.read(numBytes)
    tempHash = [0] * HASH_SIZE
    self.xorhash([ord(_) for _ in tempdata], tempHash)
    self.xorhash(tempHash, self.pcrs[pcr])
    f.close()
  
  def start(self):
    #self.delay(100)
    #first check to see if the build directory exists
    # if not then we will have to make build just so we can do the poll generation
    if not os.path.exists(cb_path) :
      subprocess.call(['make', 'build'])
  
    loadObjdumpOffsets()
    self.pcrs = [ [0 for _ in range(HASH_SIZE)] for __ in range(MAX_PCRS)]
    self.badOffsets = getHexdumpDifferences()
    self.badOffsets_sorted = self.badOffsets.keys()
    self.badOffsets_sorted.sort()

    self.cb_header, self.patched_header = loadObjdumpHeaderOffsets()
    for _ in self.cb_header :
      if _ not in self.patched_header :
        print "WARNING: [%s] does not exist in patched" % _
      else :
        if (self.cb_header[_][0] != self.patched_header[_][0] or
           self.cb_header[_][1] != self.patched_header[_][1] or
           self.cb_header[_][2] != self.patched_header[_][2]) :

          print "WARNING: [%s] is not the same as [%s] " % (str(self.cb_header[_]), str(self.patched_header[_]))
    self.bCheckBin = False

  def _choose(self):
    pass #nothing to do
   
  def _extendSection(self, sect, pcr) :
    sectStartAddr = self.cb_header[sect][1]
    sectSize = self.cb_header[sect][0]
    sectFileOff = self.cb_header[sect][2] 
    sectFileEnd = sectFileOff + sectSize
    
    #print "%s %u %u" % (sect, sectStartAddr, sectSize)
    curFileOff = sectFileOff 
    for _ in self.badOffsets_sorted :
      if (_ >= curFileOff) and (_ <= sectFileEnd) :
        #_ marks the END of the current region
        newSize = _ - curFileOff - 1 #this is the total size
        #The startAddr (in memory)
        startAddr = curFileOff - sectFileOff + sectStartAddr

        if (newSize > 0) :
          self.write("E %x %x %x\n" % (pcr, startAddr, newSize))
          self.extendHash(pcr, curFileOff, newSize)
        
        #we need to update the current file Offset
        curFileOff = _ + self.badOffsets[_]

    if curFileOff < sectFileEnd :
      newSize = sectFileEnd - curFileOff - 1 #this is the total size
      startAddr = curFileOff - sectFileOff + sectStartAddr
      self.write("E %x %x %x\n" % (pcr, startAddr, newSize))
      self.extendHash(pcr, curFileOff, newSize)

  def _extend(self):
    pcr = random.choice(pcrNums)
    if not self.bCheckBin :
      self._extendSection(".text", pcr)
      self._printPCR(pcr)
      pcr = random.choice(pcrNums)
      self._extendSection(".data", pcr)
      self._printPCR(pcr)
      self.bCheckBin = True
    else :
      newSize = random.randint(1, 0xFFF)

      #NOTE: We start at 0x8060000 because the binary should stop there.
      startAddr = random.randint(0x08060000, MAGIC_PAGE - newSize - 1)
 
      self.write("E %x %x %x\n" % (pcr, startAddr, newSize))
      self._printPCR(pcr)
      

  def _xorhash(self) :
    l = random.randint(1, MAX_HASH_TEST)
    randStr = [ random.randint(0,255) for i in xrange(l) ]
    expectedHash = [0] * HASH_SIZE
    self.xorhash(randStr, expectedHash)
    self.write("H %x\n" % l)
    self.write("".join([ chr(_) for _ in randStr]))
    self.read(delim='\n', expect=self.hashToStr(expectedHash))

  def _printPCR(self, pcr) :
    self.write('P %x\n' % pcr)
    self.read(delim='\n', expect=self.hashToStr(self.pcrs[pcr]))
   
  def _reset(self):
    i = 0
    while i < MAX_PCRS :
      self.pcrs[i] = [i] * HASH_SIZE
      i += 1

    self.write('R\n')
    pcr = random.choice(pcrNums)
    self._printPCR(pcr)

  def _zero(self):
    pcr = random.choice(pcrNums)
    self.pcrs[pcr] = [0] * HASH_SIZE
    self.write('Z %x\n' % pcr)
    self._printPCR(pcr)

  def end(self):
    ri = random.randint(0,100)
    if ri < 10 :
      self.write('P %x\n' % random.randint(MAX_PCRS,100))
    elif ri < 20 :
      self.write('Z %x\n' % random.randint(MAX_PCRS,100))
    elif ri < 30 :
      self.write('E X I T\n')
    else :
      self.write(random.choice("ABCDFGIJKLMNOQSTUVWXY") + '\n')

