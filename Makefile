# ========================
# 	DIRECTORIES
# ========================
SOURCEDIR	:= src
TESTSDIR	:= tests
BUILDDIR	:= build
BINDIR		:= bin

# ========================
# 	COMPILER
# ========================
CC      := gcc -std=c11
CFLAGS	:= -Wall -g

# ========================
# 	BINARY
# ========================
TESTS		:= $(shell find $(TESTSDIR) -name '*.c')
TESTSBIN	:= $(patsubst $(TESTSDIR)/test_%.c, $(BINDIR)/%, $(TESTS))

.PHONY: compile test clean

compile: $(BUILDDIR) $(BINDIR) $(TESTSBIN)
	echo $(TESTSBIN)

test: compile
	./runtests.sh

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

$(BINDIR)/%: $(TESTSDIR)/test_%.c $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -I$(SOURCEDIR) $< -o $@

$(BUILDDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@
