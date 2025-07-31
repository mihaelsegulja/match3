CC = gcc
CFLAGS = -Wall -std=c99 $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)
SRC = src/main.c
OUTDIR = build
OUT = $(OUTDIR)/match3

all:
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf $(OUTDIR)
