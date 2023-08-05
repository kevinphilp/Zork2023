# Variables set after target match
# $@ full target
# $* target minus suffix
# $< first prerequisite
# $^ All prerequisities
# -g2 is default, -g3 doesnt work with all debuggers, -ggdb is for gdb
# -Og is optimise for debugging.
# -fms-extensions -Wno-microsoft for combining structs

GCC = gcc
CLANG = clang
TCC = tcc

# -g3 emits macro info, don't use ggdb anymore
CFLAGS = -g3 -Wall -O0 -Wextra -pipe -std=c11 -Wpedantic -Wshadow -fms-extensions
# CXFLAGS= $(shell pkg-config --cflags --libs glib-2.0)
CXFLAGS= $(shell pkg-config --cflags)

CMAIN = main.c
CLIBS = kputils.c bag.c
COBJS = $(CLIBS:.c=.o)
PROGRAM = main

########### GCC

gcc: $(CMAIN) $(COBJS)
	$(GCC) $(CFLAGS) $(CXFLAGS) -o $(PROGRAM) $^

%.o: %.c
	$(GCC) $(CFLAGS) $(CXFLAGS) -c  $^

libs: $(CLIBS)
	$(GCC) $(CFLAGS) $(CXFLAGS) -c $^

########### TCC

tcc: $(CMAIN) $(COBJS)
	$(TCC) $(CFLAGS) $(CXFLAGS) -o $(PROGRAM) $^

%.o: %.c
	$(TCC) $(CFLAGS) $(CXFLAGS) -c  $^

tcclibs: $(CLIBS)
	$(TCC) $(CFLAGS) $(CXFLAGS) -c $^


######## CLANG

clang: $(CMAIN) $(COBJS)
	$(CLANG) $(CFLAGS) $(CXFLAGS) -o $(PROGRAM) $^

%.o: %.c
	$(CLANG) $(CFLAGS) $(CXFLAGS) -c  $^

clanglibs: $(CLIBS)
	$(CLANG) $(CFLAGS) $(CXFLAGS) -c $^


######### MISC

clean:
	rm -f *.o *.so *.a *.gch
