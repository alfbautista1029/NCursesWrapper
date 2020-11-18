# NCursesWrapper
A object oriented wrapper for the NCurses Library

This wrapper groups together ncurses data structures, like windows, into classes to make it easier to declare, initialize and use ncurses functionality.

This wrapper depends on the NCurses library, so please make sure you have the library installed on your machine. 

Platform-Dependent Installation Processes: 

MacOS
-----
 MacOS comes with NCurses pre-installed (libncurses.5.4)
 
When compiling an ncurses program, make sure to link the ncurses library using the compile flag "-lncurses" AFTER your source code (otherwise, your linker will throw an error.)
  
  Example: "g++ ncurses_prog.c -lncurses -o ncurses_prog.o"

Linux
-----
 Installation of ncurses on a linux machine varies on the distribution of the OS you're using:
 
 For Debian distributions,
  Install the library using the command
    
    "sudo apt-get install libncurses5-dev libncursesw5-dev"

 CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older,
  Install the library using the command:
    
      "sudo yum install ncurses-devel"

If you don't have the aforementioned distributions or you have a different distribution or package manager, please check your package manager to check if the ncurses library is available for download and installation.

Windows
-------
There is no official ncurses library for Windows. However you can look into PDCurses, a windows port of the ncurses library.
