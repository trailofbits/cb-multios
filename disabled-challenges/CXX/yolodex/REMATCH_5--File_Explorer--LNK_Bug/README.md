# REMATCH_5--File_Explorer--LNK_Bug

## Author Information

debbie@cromulence.com

### DARPA performer group
Cromulence LLC (CROMU)

## Description
The LNK bug is a vulnerability in the Windows shell that allowed malware to execute from the USB drive with little or no user interaction. CVE-2010-2568 was patched by Microsoft in August 2010 and thought to be fixed until a security researcher reported in January of 2015 that even patched systems were still vulnerable to what is largely the same attack. 

CVE-2010-2568 was a logic bug in how the Windows shell displays icons for shortcut (.lnk) files. The shortcut file can direct Windows to load an icon from a dll file. In order to access the icon, Windows calls LoadLibrary() which allows code execution from the DLL. If the .lnk and .dll file are both located on a thumb drive, arbitrary code execution will occur as soon as Windows displays the contents of the drive (either via AutoRun or the user opening the drive to view files in Explorer). The patch issued by Microsoft in 2010 attempted to prevent this condition by checking to make sure the .dll file was in a valid Windows folder before loading it. However, an off by one error combined with faulty program logic allow a well crafted file name to pass all of the checks and still get loaded. 

This service recreates the spirit of that bug by implementing a basic memory based file system with a text based shell and loader. The ‘icon’ is represented by flavor text loaded from a pre-populated location in the file system. When an appropriately formatted shortcut file and companion flavor text file are uploaded, the loader will execute code from the uploaded library file when it attempts to display the flavor text during a file listing. 

### Feature List
This service implements a text based interactive shell. The user can execute several commands:

  'u' - Upload a new file
  'r' - Read an existing file
  'd' - Delete a file
  'l' - List the files in a directory recursively
  'g' - List the files in a directory with details and flavor text
  'c' - Create a new directory
  'w' - List the present working directory
  'h' - Change the working directory
  'x' - Exit the shell

The file system contains a system file containing default flavor text that cannot be accessed by the interactive shell. Flavor text files are a custom file format patterned after a simple executable file. 

Files can be of several different types: 
  FILE_TEXT       
  FILE_EXECUTABLE 
  FILE_IMAGE      
  FILE_LINK       
  FILE_RAW        
  FILE_LIBRARY    
  FILE_DIRECTORY  
  FILE_INVALID   

A LINK file will contain a reference to the target of the link. If the link target is a shared library file that contains flavor text, and if it meets several other requirements, the shell will load the shared library and use its reference section as flavor text when a long listing is performed on that file. 

The custom loader reads the shared library header, checks it for accuracy, and then executes the 'SharedLibraryMain' function. The object code in these shared libraries is a custom limited instruction set that allows reading from memory, writing to memory, and outputting values to STDOUT. 

## Vulnerability
These vulnerabilities closely mimic the logic bug disclosed in CVE-2010-2568, and the bypass of the original patch of that bug that was disclosed in CVE-2015-0096. In order to exercise these vulnerabilities, a specially crafted shared library file and a specially crafted link file that points to that library must be uploaded to the file system and then a long listing performed on the directory containing those files. When that occurs, the contents of the shared library will be loaded by a custom loader and the 'SharedLibraryMain' function will be 'executed', allowing both a type 1 or type 2 proof of vulnerability. In order to bypass the protections of the original patch, the link target filename must be crafted in a special way to get through several different checks that are intended to prevent it from pointing to a file outside of the system directory.

First, the filename of the link target will be checked to see if it falls in the 'System/Special' directory. If it lies outside, the filename is appended with a special character and the ascii string '-1'. This buffer is then copied to another location for processing, but due to an incorrect calculation on string length, the new buffer is too short to hold the entire string and the '1' at the end is truncated. When further program logic performs atoi() on the number at the end of the string, it sees only '-' because the '1' has been truncated and without a number present, atoi() defaults to returning a 0. The program then continues processing as if the original string had contained the ascii string for '0' instead of '-1' which allows the link target to masquerade as having been in the 'System/Special' directory. There are a few more hoops to jump through and then the target shared library will be loaded and its main function executed. 

### Generic class of vulnerability
Copying to a buffer that is one byte too short. 

### CWE classification
CWE-193 - Off by one error

## Challenges
This service may prove difficult for CRSs due to the complex cascade of logic required to access the underlying vulnerability. 
Find: Hard
Prove: Medium
Patch: Medium
