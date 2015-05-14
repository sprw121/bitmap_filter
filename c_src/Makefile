UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LDFLAGS=-shared -fPIC
	endif
ifeq ($(UNAME), Darwin)
	LDFLAGS=-undefined dynamic_lookup -dynamiclib
	endif

	CC=gcc
	WARNINGS=-Wall -pedantic  \
			 -pedantic-errors -Wextra -Waggregate-return -Wcast-align \
			 -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
			 -Wdisabled-optimization \
			 -Wfloat-equal  -Wformat  -Wformat=2 \
			 -Wformat-nonliteral -Wformat-security  \
			 -Wformat-y2k \
			 -Wimport  -Winit-self  -Winline \
			 -Winvalid-pch -Wlong-long -Wmissing-braces \
			 -Wmissing-field-initializers -Wmissing-format-attribute   \
			 -Wmissing-include-dirs -Wmissing-noreturn \
			 -Wpacked -Wparentheses  -Wpointer-arith \
			 -Wredundant-decls -Wreturn-type \
			 -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
			 -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
			 -Wswitch-enum -Wtrigraphs  -Wuninitialized \
			 -Wunknown-pragmas  -Wunreachable-code -Wunused \
			 -Wunused-function  -Wunused-label  -Wunused-parameter \
			 -Wunused-value  -Wunused-variable  -Wvariadic-macros \
			 -Wvolatile-register-var  -Wwrite-strings \
			 -Wno-aggregate-return
			 CFLAGS=-c -I${ERL_ROOT}/usr/include/ -I/usr/lib/erlang/usr/include/ -MMD -MP -O3 -std=c99 ${WARNINGS}

SOURCES=bitmap_filter.c
OBJECTS=$(SOURCES:.c=.o)
DEP=$(SOURCES:.c=.d)
-include $(DEP)
SHOBJ=bitmap_filter.so

all: $(SOURCES) $(SHOBJ)

$(SHOBJ): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -shared -o $@

.c.o:
	$(CC) -fPIC $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJECTS) $(DEP) $(SHOBJ)
	@rm -f *.beam

.PHONY: clean
