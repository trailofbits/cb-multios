#!/usr/bin/python

import sys
import glob

MAX_LINKS = 10

files = glob.glob(sys.argv[1])
print "char* gPageData[MAX_LINKS][2] = {"
pagesInfo = [0 for i in xrange(10)]
i = 0;

for f in files :
  print "  {\"" + f + "\","
  lines = open(f)
  for l in lines :
    print "  \"" + "".join([ "\\x%02x" % ord(c) for c in l ]) + "\""
    pagesInfo[i] += len(l)
    
  print "  },"

  i += 1
  if i >= 10 :
    break

for j in xrange(i, MAX_LINKS) :
  print "  {\"\",\"\"},"

print "};"

print "void init_pages()"
print "{"
print "  for (size_t i = 0; i < MAX_LINKS; i++)"
print "  {"
print "    gPages[i].name = gPageData[i][0];"
print "    gPages[i].data = gPageData[i][1];"
print "    gPages[i].links[0] = &gPages[i];"
print "  }"

for i in xrange(MAX_LINKS) :
  print "  gPages[%d].len = %d;" % (i,pagesInfo[i])

print "}"

