# ========================
# 	DIRECTORIES
# ========================
SOURCEDIR	:= src
TESTSDIR	:= tests
BINDIR		:= bin

# ========================
# 	COMPILER
# ========================
CC      := gcc -std=c11
CFLAGS	:= -Wall -g

# ========================
# 	BINARY
# ========================
SOURCES		:= $(shell find $(SOURCEDIR) -name '*.c')
TESTS		:= $(shell find $(TESTSDIR) -name '*.c')
TESTSBIN	:= $(patsubst $(TESTSDIR)/%.c, $(BINDIR)/%, $(TESTS))

.PHONY: compile-tests test clean

compile-tests: $(BINDIR) $(TESTSBIN)

test: compile-tests
	./runtests.sh

clean:
	rm -rf $(BINDIR)

$(BINDIR)/%: $(TESTSDIR)/%.c $(SOURCES)
	$(CC) $(CFLAGS) -I$(SOURCEDIR) $< -o $@

$(BINDIR):
	mkdir -p $@
