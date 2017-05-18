# Ghost_In_The_CGC

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

You open your eyes and find yourself in a large barely lit room. Your head hurts, are disoriented and have no idea what to do. So, you do what anyone who has ever watched a movie would do, yell out for help. Will you be helped? Or will you be stuck forever? 

This CB is a text based game where the user has to help Bob escape his fate. The game itself takes place within the world of a Cyber Grand Challenge challenge binary. Bob is effectively stuck within the world of a CB with seven "portals" corresponding to the seven system calls and seven. As one might expect, helping Bob survive involves leading him towards the "transmit" portal which will magically transport Bob to your keyboard. 

This CB is designed to utilize a known self protection technique that checks to make sure that the software has not been altered from the factory delivered version. This is made popular by the Warden Client - used by Blizzard Entertainment to detect cheaters - see (https://en.wikipedia.org/wiki/Blizzard_Entertainment#Technology)[https://en.wikipedia.org/wiki/Blizzard_Entertainment#Technology]. 

## Self Protection:

Our self protection scheme is a bit different from that of Blizzard's because we do not have an active server connection that can be used to obtain the golden hash of the software. Our protection system must therefore do all of the comparisons in software.

In particular, the self protection mechanism consists of three parts:

1. Heap Protection is afforded by a function that allocates as many pages as is allowed during testing. Once that value is determined, it is hardcoded into the software and so if the software is not able to allocate the number of pages as expected, this test will fail and the software will exit.

2. Data Protection calculates a hash of the DATA section of the binary and compares that with one that was calculated previously

3. Text Protection calcuates a hash of the TEXT section of the binary. There are some parts of the text section that are ignored due to the need to have the hash match between the patched and unpatched versions.

### Patching the binary:
The self protection should pose a challenge for patching although the challenge isn't as big as it might seem. 

The competitor can simply disable the self protection mechanism by NOPing out the call to selfProtect in the first place. It doesn't affect the binary's functionality. This is in fact a common way to defeat protections that are built directly into binaries.

The competitor can also simply reduce the size of the read in the call to receive. This will effectively patch the buffer overflow vulnerability without affecting the self protection measurement since we ignore that instruction during measurement.

## Vulnerability Class:

There are two vulnerabilities. 

The first is a classic stack buffer overflow (CWE-121: Stack-based Buffer Overflow) which results in a type 1 POV. This is straight forward. 

The second vulnerability is the an information disclosure vulnerability which is in fact part of the game (CWE-291: Information Exposure Through Sent Data). In particular, there is a part of the game where Bob is instructed to read the color of some lights that are within the room. As it turns out, these lights correspond to the bit value of memory - that is Green is 1, White is 0 and Black is un-allocated or invalid address.

## Notes:

The "warden" system requires some predefined hashes. In particular, we need 1. the number of available pages, 2. the hash of the TEXT section and 3. the hash of the DATA section of the executable. To do this, we will have to use GDB. There are three basic steps. We have created a python script support/calculateOffsets.python to do all of this automatically. 

1. Set the variable of interest to something noticeable such as 0xCAFEBABD

2. build the binary and then use objdump to identify the instruction's address
	$ make build
	$ /usr/i386-linux-cgc/bin/objdump -d bin/YAN01_00015 | grep cafebabd
3. Use a gdb script to dump the contents
	$ gdb -x findMemsize.gdb bin/YAN01_00015

Before we do this, we will first have to populate the skip sections though. To do that, we will rely on objdump. for example:

	vagrant@crs:/vagrant/YAN01_00015$ /usr/i386-linux-cgc/bin/objdump -d bin/YAN01_00015_patched > build/YAN01_00015_patched.dump
	vagrant@crs:/vagrant/YAN01_00015$ /usr/i386-linux-cgc/bin/objdump -d bin/YAN01_00015 > build/YAN01_00015.dump
	vagrant@crs:/vagrant/YAN01_00015$ diff build/YAN01_00015.dump build/YAN01_00015_patched.dump 
	2c2
	< bin/YAN01_00015:     file format cgc32-i386
	---
	> bin/YAN01_00015_patched:     file format cgc32-i386
	388c388
	<  80486c8:	3d 00 00 00 00       	cmp    $0x0,%eax
	---
	>  80486c8:	3d 00 c0 47 43       	cmp    $0x4347c000,%eax
	490c490
	<  80488ab:	b9 00 01 00 00       	mov    $0x100,%ecx
	---
	>  80488ab:	b9 80 00 00 00       	mov    $0x80,%ecx
	495c495
	<  80488c6:	c7 44 24 08 00 01 00 	movl   $0x100,0x8(%esp)
	---
	>  80488c6:	c7 44 24 08 80 00 00 	movl   $0x80,0x8(%esp)
	1058,1059c1058,1059
	<  804910c:	68 c8 f8 04 08       	push   $0x804f8c8
	<  8049111:	68 37 03 05 08       	push   $0x8050337
	---
	>  804910c:	68 00 00 00 00       	push   $0x0
	>  8049111:	68 00 00 00 00       	push   $0x0

Given this, we will arrive at the following definition for skips that goes into the c source file

	TextProtectSkip skips[NUM_SKIPS] = { {0x80486c8,5}, {0x80488ab,5}, {0x80488c6,7}, {0x804910c,10}, {0x8048210,7}};

Notice how I added an extra at the end, which is the contents of the instruction with the text hash value - we can't include it, otherwise it will mess things up
	
So for example, we first set EXPECTED_MEMSIZE, EXPECTED_TEXT_HASH and EXPECTED_DATA_HASH to 0xCAFEBABD, 0xCAFEBABE and 0xCAFEBABF respectively.
Then we can build it and run objdump to find the addresses:

	$ make build
	$ /usr/i386-linux-cgc/bin/objdump -d bin/YAN01_00015 | grep cafebab
	 804810b:	81 7d f4 bd ba fe ca 	cmpl   $0xcafebabd,-0xc(%ebp)
	 8048210:	81 7d fc be ba fe ca 	cmpl   $0xcafebabe,-0x4(%ebp)
	 8048280:	81 7d fc bf ba fe ca 	cmpl   $0xcafebabf,-0x4(%ebp)


Based on those, we created three files

Here is a file named "findMemsize.gdb"
	break *0x804810b
	r
	x /x $ebp-0xc
	quit
	
findDataHashes.gdb
	break *0x8048280
	r
	x /x $ebp-0x4
	quit

findTextHashes.gdb
	break *0x8048210
	r
	x /x $ebp-0x4
	quit

We will now have to execute them in order. We can do findMemsize first, to get the memSize and then build and repeat the next one.
	
Here is an execution of findMemsize.gdb
	$ gdb -x findMemsize.gdb bin/YAN01_00015
	...
	Breakpoint 1 at 0x804810b
	
	Breakpoint 1, 0x0804810b in ?? ()
	0xbaaaaef8:	0x000bffc1
	
Notice that the value is bffc1, so we need to update the code to bffc1

Repeating with findDataHashes.gdb
	$ gdb -x findDataHashes.gdb bin/YAN01_00015	
	Breakpoint 1 at 0x8048280
	
	Breakpoint 1, 0x08048280 in ?? ()
	0xbaaaaf00:	0x61e980f1

Finally repeating with findTextHashes.gdb
	$ gdb -x findTextHashes.gdb bin/YAN01_00015	
	Breakpoint 1 at 0x8048210
	
	Breakpoint 1, 0x08048210 in ?? ()
	0xbaaaaf00:	0x9fd7d7c8

### Generating the script
The script is built into the machine.py file. It can be changed if needed, however, if changes are made to the script, a new script.h must be generated. The easiest way to do this is to copy the contents of machine.py from lines 5-297 into another file (e.g. temp.py) 

Then edit temp.py to dump the header file by making the change from
	#print head.toCDef()
	
	applyPatches()
	
	#print patchesToC()

to

	print head.toCDef()
	
	#applyPatches()
	
	print patchesToC()

This will print the script to STDOUT, thus we should run it as
	python temp.py > src/script.h

