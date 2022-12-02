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
TESTS		:= $(shell find $(TESTSDIR) -name '*.c')
TESTSBIN	:= $(patsubst $(TESTSDIR)/test_%.c, $(BINDIR)/%, $(TESTS))

.PHONY: compile test clean

compile: $(BINDIR) $(TESTSBIN)

	echo $(TESTSBIN)
test: compile
	./runtests.sh

clean:
	rm -rf $(BINDIR)

$(BINDIR)/%: $(TESTSDIR)/test_%.c $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -I$(SOURCEDIR) $< -o $@

$(BINDIR):
	mkdir -p $@
