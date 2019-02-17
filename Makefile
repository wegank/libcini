#!/usr/bin/make

CC = gcc

SOURCEDIR   = src
DATADIR     = share

OUTPUTDIR   = out
LIBDIR      = $(OUTPUTDIR)/usr/lib
INCLUDEDIR  = $(OUTPUTDIR)/usr/include
SHAREDIR    = $(OUTPUTDIR)/usr/share/libcini

SOURCES = $(shell echo $(SOURCEDIR)/*.c)
LIBRARY = libcini.so

CFLAGS      = -Wall -fPIC -shared -Wl,-soname,$(LIBRARY) -lSDL2_ttf -lSDL2

all: $(SOURCES)
	mkdir -p $(LIBDIR) $(INCLUDEDIR) $(SHAREDIR)
	cp $(SOURCEDIR)/*.h $(INCLUDEDIR)
	cp $(DATADIR)/font.ttf $(SHAREDIR)
	$(CC) $(SOURCES) -o $(LIBDIR)/$(LIBRARY) $(CFLAGS)

deb: all
	mkdir -p $(OUTPUTDIR)/DEBIAN
	cp control $(OUTPUTDIR)/DEBIAN
	dpkg-deb -b out prebuilt/libcini-debian-64bit.deb
	
clean:
	rm -r $(OUTPUTDIR)

