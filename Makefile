# Bibleajax program
# Bob Kasper, MVNU Computer Science
# updated January 2020 to use
# c++11 compiler option, current paths on cs.mvnu.edu

# This is a Makefile for the Bible web app demo program.
# Copy this directory to a location within your home directory.
# Change the USER name value below to your own user name.
# Then use "make" to build the server program,
# and deploy it to the live web server directory.
# To test the program, go to http://cs.mvnu.edu/class/csc3004/USER/
# and open the bibleindex.html link.

# TODO: Must replace "username" by your username
USER= shabusch

# Use GNU C++ compiler with C++11 standard
CC= g++
CFLAGS= -g -std=c++11 -Wall   # Added -Wall to show warnings

# ADDED lookupserver + fifo support
all:	lookupclient.cgi PutCGI PutHTML testreader lookupserver

# TODO: For bibleajax.cgi, add dependencies to include
# compiled classes from Project 1 to be linked into the executable program

# ADDED fifo.o dependency
lookupclient.cgi:	lookupclient.o fifo.o
	$(CC) $(CFLAGS) -o lookupclient.cgi lookupclient.o fifo.o -lcgicc

# main program to handle AJAX/CGI requests for Bible references

lookupclient.o:	lookupclient.cpp fifo.h
	$(CC) $(CFLAGS) -c lookupclient.cpp

# TODO: copy targets to build classes from Project 1:
# Bible.o, Ref.o, Verse.o

# Ref Object
Ref.o : Ref.h Ref.cpp
	$(CC) $(CFLAGS) -c Ref.cpp

# Verse Object
Verse.o : Ref.h Verse.h Verse.cpp
	$(CC) $(CFLAGS) -c Verse.cpp

# Bible Object
Bible.o : Ref.h Verse.h Bible.h Bible.cpp
	$(CC) $(CFLAGS) -c Bible.cpp

fifo.o: fifo.cpp fifo.h
	$(CC) $(CFLAGS) -c fifo.cpp

lookupserver: lookupserver.o Ref.o Verse.o Bible.o fifo.o
	$(CC) $(CFLAGS) -o lookupserver lookupserver.o Ref.o Verse.o Bible.o fifo.o

lookupserver.o: lookupserver.cpp Ref.h Verse.h Bible.h fifo.h
	$(CC) $(CFLAGS) -c lookupserver.cpp

# Testreader program for Project 3
testreader: testreader.o Ref.o Verse.o Bible.o
	$(CC) $(CFLAGS) -o testreader testreader.o Ref.o Verse.o Bible.o

testreader.o: testreader.cpp Ref.h Verse.h Bible.h
	$(CC) $(CFLAGS) -c testreader.cpp

PutCGI:	lookupclient.cgi
	chmod 755 lookupclient.cgi
	cp lookupclient.cgi /var/www/html/class/csc3004/$(USER)/cgi-bin

	echo "Current contents of your cgi-bin directory: "
	ls -l /var/www/html/class/csc3004/$(USER)/cgi-bin/

PutHTML:
	cp bibleindex.html /var/www/html/class/csc3004/$(USER)

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/csc3004/$(USER)

clean:
	rm *.o core lookupclient.cgi testreader lookupserver