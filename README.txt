Description:
	my port of Hunt the Wumpus to c for Linux and FreeDOS

Linux:
	run build.sh to compile c code
FreeDOS:
	included under freedos folder is the wumpDos.img floppy image
	1) write wumpDoS.img to floppy (use Linux (cat or dd to floppy drive) or FreeDOS (rawrite to floppy drive) for this)  
	2) boot with floppy in drive
	3) copy .zip & .bat files to C:\devel\watcom
	4) make directory C:\devel\watcom\wumpus
	5) move .zip and .bat files into C:\devel\watcom\wumpus
	4) unzip zip file
	5) set environment run C:\devel\watcomc\owsetenv.bat
	6) run C:\devel\watcom\wumpus\compile.bat to compile
	7) delete .obj files
	8) copy fisher_y.exe wumpus.exe
	9) delete fisher_y.exe
	10) copy wumpus.exe C:\freedos\bin
	11) delete *.zip file

	game is now installed
	leave source code in C:\devel\watcomc

	optional:
		compiles as fisher_y.exe
		rename excutable to something else (i.e wumpus.exe)
		delete .obj files
		copy executable to somewhere in PATH
