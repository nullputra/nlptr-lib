# usage:
# $ make proj=./src/main.cpp relout
# $ make proj=./src/main.cpp dbgout
# $ make proj=./src/main.cpp dbgrun

# ----------------------------------------------------------

# Note that spaces at the end of lines are not ignored in Makefile.
PROJ	= $(proj)
PROJNAME= $(basename $(notdir $(PROJ)))
PROJSFX	= $(suffix $(PROJ))
INPUT	= ./input.txt
DBGOUT	= ./bin/out/$(PROJNAME).dbg
RELOUT	= ./bin/out/$(PROJNAME).rel

# c
CC		= gcc
CFLAGS	= -g -O2 -W -Wno-unused-result -Wshadow -Wparentheses -Wmaybe-uninitialized
ifneq ($(origin extraFlag), undefined)
CFLAGS	+= $(extraFlag)
endif

# c++
CXX		= g++
CXXINC	= -I./lib/cpp
CXXFLAGS= -g -O2 -std=c++17 -Wchar-subscripts -Wmaybe-uninitialized -Wmissing-field-initializers -Wparentheses -Wshadow -Wsign-compare -Wunused-but-set-variable -Wunused-parameter -Wunused-variable $(CXXINC)
ifeq ($(findstring t, $(PROJNAME)),)
CXXFLAGS += -D_DEBUG_HPP
endif
DBGHPP	= ./lib/cpp/others/debug.hpp
ifneq ($(origin extraFlag), undefined)
CXXFLAGS+= $(extraFlag)
endif

# c#
CS		= dotnet build -p:StartupObject=$(PROJNAME)
CSOUT	= ./bin/Debug/netcoreapp3.1/ComPro
$(CSOUT): $(PROJ)
	$(CS)

# lisp (compile, run)
LCOMP	= sbcl --noinform --eval "(compile-file \"$(PROJ)\")" --quit
LRUN	= sbcl --script
LTMP	= "$(patsubst %.lisp,%.fasl,$(PROJ))"
LOUT	= ./bin/out/$(PROJNAME).fasl
$(LOUT): $(PROJ)
	$(LCOMP)
# https://beiznotes.org/multiple-lines-in-makefile/
	@if [ -f $(LTMP) ]; then \
		mv $(LTMP) $@;       \
	else                     \
		exit 1;              \
	fi

# go
GO		= go build

# rust
RS		= cargo build
RSFLAGS	=  --bin $(PROJNAME)
RSDBGOUT= ./target/debug/$(PROJNAME)
RSRELOUT= ./target/release/$(PROJNAME)

# python
PY		= python3
# -B: Don't generate *.pyc file.
# PYFLAGS	= -B

# ----------------------------------------------------------
# ------------------------- relout -------------------------

.PHONY: relout

# c
ifeq ($(PROJSFX), .c)
$(RELOUT): $(PROJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm
relout: $(RELOUT)

# c++
else ifeq ($(PROJSFX), .cpp)
$(RELOUT): $(PROJ) $(DBGHPP)
	$(CXX) $(CXXFLAGS) -o $@ $<
relout: $(RELOUT)

# c#
else ifeq ($(PROJSFX), .cs)
$(RELOUT): $(CSOUT)
relout: $(RELOUT)

# lisp
else ifeq ($(PROJSFX), .lisp)
$(RELOUT): $(LOUT)
relout: $(RELOUT)

# go
else ifeq ($(PROJSFX), .go)
$(RELOUT): $(PROJ)
	$(GO) -o $@ $<
relout: $(RELOUT)

# rust
else ifeq ($(PROJSFX), .rs)
$(RSRELOUT): RSFLAGS += --release
$(RSRELOUT): $(PROJ)
	$(RS) $(RSFLAGS)
$(RELOUT): $(RSRELOUT)
	@cp -f $^ $@
relout: $(RELOUT)

# Interpreter Type Language
else
relout:; @echo No compilation is required.

endif

# ------------------------- relout -------------------------
# ------------------------- dbgout -------------------------

.PHONY: dbgout

# c
ifeq ($(PROJSFX), .c)
$(DBGOUT): CFLAGS += -D_DEBUG
$(DBGOUT): $(PROJ)
	$(CC) $(CFLAGS) -o $@ $< -lm
dbgout: $(DBGOUT)

# c++
else ifeq ($(PROJSFX), .cpp)
$(DBGOUT): CXXFLAGS += -D_DEBUG -D_GLIBCXX_DEBUG
$(DBGOUT): $(PROJ) $(DBGHPP)
	$(CXX) $(CXXFLAGS) -o $@ $<
dbgout: $(DBGOUT)

# c#
else ifeq ($(PROJSFX), .cs)
$(DBGOUT): $(CSOUT)
dbgout: $(DBGOUT)

# lisp
else ifeq ($(PROJSFX), .lisp)
$(DBGOUT): $(LOUT)
relout: $(DBGOUT)

# go
else ifeq ($(PROJSFX), .go)
$(DBGOUT): $(PROJ)
	$(GO) -o $@ $<
dbgout: $(DBGOUT)

# rust
else ifeq ($(PROJSFX), .rs)
$(RSDBGOUT): $(PROJ)
	$(RS) $(RSFLAGS)
$(DBGOUT): $(RSDBGOUT)
	@cp -f $^ $@
dbgout: $(DBGOUT)

# Interpreter Type Language
else
dbgout:; @echo No compilation is required.

endif

# ------------------------- dbgout -------------------------
# ------------------------- dbgrun -------------------------

.PHONY: dbgrun

# python
ifeq ($(PROJSFX), .py)
dbgrun:; $(PY) $(PROJ) < $(INPUT)

# c#
else ifeq ($(PROJSFX), .cs)
dbgrun: $(CSOUT)
	$^ < $(INPUT)

# lisp
else ifeq ($(PROJSFX), .lisp)
dbgrun: $(LOUT)
	$(LRUN) $^ < $(INPUT)

# Compiler Type Language
else
dbgrun: $(DBGOUT)
	$^ < $(INPUT)

endif

# ------------------------- dbgrun -------------------------
