#!/usr/bin/make

CC = gcc

SOURCEDIR   = src
DATADIR     = share

OUTPUTDIR   = out
LIBDIR      = $(OUTPUTDIR)/usr/lib
INCLUDEDIR  = $(OUTPUTDIR)/usr/include
SHAREDIR    = $(OUTPUTDIR)/usr/share/libcini

SOURCES = $(shell echo $(SOURCEDIR)/*.c)
OBJECTS = $(SOURCES:$(SOURCEDIR)/%.c=%.o)
LIBRARY = libcini.so

OBJ_CFLAGS  = -c -Wall -fPIC
CFLAGS      = -shared -Wl,-soname,$(LIBRARY) -lSDL_ttf -lSDL

all: $(SOURCES) $(LIBRARY)
	mkdir -p $(LIBDIR) $(INCLUDEDIR) $(SHAREDIR)
	cp $(LIBRARY) $(LIBDIR)
	cp $(SOURCEDIR)/*.h $(INCLUDEDIR)
	cp $(DATADIR)/font.ttf $(SHAREDIR)
	rm -f $(OBJECTS) $(LIBRARY) *~

$(LIBRARY): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CFLAGS)

%.o: $(SOURCEDIR)/%.c
	$(CC) $(OBJ_CFLAGS) $< -o $@

deb: all
	mkdir -p $(OUTPUTDIR)/DEBIAN
	cp control $(OUTPUTDIR)/DEBIAN
	dpkg-deb -b out prebuilt/libcini-debian-64bit.deb
	
