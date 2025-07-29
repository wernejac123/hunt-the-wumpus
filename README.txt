Description:
	my port of Hunt the Wumpus to c for Linux and FreeDOS

Linux:
	run build.sh to compile c code (C99 standard). This shell script 
        only compiles it and not install. I usually put it under /usr/local.
FreeDOS:
	included under freedos folder is the wumpDos.img floppy image
	1) write wumpDoS.img to floppy (diskcopy, rawwrite, etc) 
	2) insert floppy in drive 
	3) set envirnment for c/c++ with:
	   C:\DEVEL\WATCOMC\OWSETENV.BAT
        4) copy contents of floppy to c drive (I put it under C:\SRC\C\WUMPUS 
        5) WCC -ZA99 FISHER_YATES.C
	   WCC -ZA99 MAIN.C
           WCL -ZA99 *.OBJ
           DEL *.OBJ
           
	      NOTE: On my FreeDOS setup fisher_yates.h & fisher_yates.c 
	      show up as FISHER~1.C & FISHER~1.H. The compile can't find 
              fisher_yates.h so I edit MAIN.C & FISHER~1.C and change the 
              line #include "fisher_yates.h" to #include "fisher~1.h"

        6) rename executable (*.EXE) to WUMP.EXE
        7) create directory C:\GAMES\WUMP if it doesn't exist yet & 
           copy contents of wumpus directory to C:\GAMES\WUMP 
           (something like XCOPY C:\SRC\C\HUNT-THE-WUMPUS C:\GAMES\WUMP /S
            and select Directory when it asks what WUMP is).
