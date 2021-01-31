# Compiler:
CC = gcc

# Definitions:
BINARY = teulu

# Directories:
SRCDIR = src
ODIR = obj
IDIR = inc

# Linking:
LDFLAGS = -lSDL -lSDL_image -lSDL_mixer -lm

# Compiler options:
CFLAGS = -std=gnu99 -I$(IDIR) $(LDFLAGS)

# Objects:
_OBJ = main.o bugs.o bumbarrel.o mobs.o predators.o screen.o sprites.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Targets:
all: teulu

$(ODIR)/%.o: $(SRCDIR)/%.c $(IDIR)/%.h $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
	mkdir $(ODIR)

teulu: $(OBJ) $()
	$(CC) -o $(BINARY) $^ $(CFLAGS)

.PHONY: clean, cleanall

clean:
	rm -rf $(ODIR)

cleanall: clean
	rm -f $(BINARY)
