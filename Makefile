# Compiler:
CC = gcc

# Definitions:
BINARY = teulu

# Directories:
SRCDIR = src
ODIR = obj
IDIR = inc

# Linking:
LDFLAGS = -lSDL -lSDL_image -lSDL_mixer -lSDL_gfx -lm

# Compiler options:
CFLAGS = -std=gnu99 -I$(IDIR) $(LDFLAGS)

# Objects:
_OBJ = main.o bugs.o bumbarrel.o mobs.o predators.o screen.o sprites.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Targets:
all: teulu dist

$(ODIR)/%.o: $(SRCDIR)/%.c $(IDIR)/%.h $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
	mkdir $(ODIR)

teulu: $(OBJ) $()
	$(CC) -o $(BINARY) $^ $(CFLAGS)

dist: teulu
	mkdir -p Teulu
	cp teulu Teulu
	cp -r resources Teulu
	cp README.md LICENSE Teulu
	zip -r $(BINARY).zip Teulu/

.PHONY: clean, cleanall

clean:
	rm -rf $(ODIR)

cleanall: clean
	rm -f $(BINARY)
	rm -rf Teulu/
	rm -f $(BINARY).zip
