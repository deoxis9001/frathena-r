
COMMON_OBJ = ../common/obj_all/showmsg.o ../common/obj_all/utils.o ../common/obj_all/strlib.o \
	../common/obj_all/minimalloc.o
COMMON_H = ../common/plugin.h ../common/cbasetypes.h \
	../common/showmsg.h ../common/utils.h ../common/strlib.h \
	../common/malloc.h

PLUGINS = sample sig pid console



#####################################################################
.PHONY : all $(PLUGINS) clean help

all: $(PLUGINS)

sample: sample.so

sig: sig.so

pid: pid.so

console: console.so

clean:
	rm -rf *.o

help:
	@echo "possible targets are $(PLUGINS:%='%') 'all' 'clean' 'help'"
	@echo "'sample'   - sample plugin"
	@echo "'sig'      - signal handler plugin"
	@echo "'pid'      - process id plugin"
	@echo "'console'  - console plugin"
	@echo "'all'      - builds all above targets"
	@echo "'clean'    - cleans builds and objects"
	@echo "'help'     - outputs this message"

#####################################################################

%.so: %.c
	gcc -g -O2 -pipe -ffast-math -Wall -Wno-sign-compare -Wno-unused-parameter -Wno-pointer-sign -Wno-switch -fno-strict-aliasing -DHAVE_SETRLIMIT -DHAVE_STRNLEN -Wno-unused -Wno-parentheses -DHAVE_MONOTONIC_CLOCK  -I../common -I/usr/include  -L/usr/lib -shared -o ../../plugins/$@ $<

sig.so: sig.c $(COMMON_OBJ)
	gcc -g -O2 -pipe -ffast-math -Wall -Wno-sign-compare -Wno-unused-parameter -Wno-pointer-sign -Wno-switch -fno-strict-aliasing -DHAVE_SETRLIMIT -DHAVE_STRNLEN -Wno-unused -Wno-parentheses -DHAVE_MONOTONIC_CLOCK  -I../common -I/usr/include  -L/usr/lib -shared -o ../../plugins/$@ $< $(COMMON_OBJ)

# missing common object files
../common/obj_all/%.o: ../common/%.c $(COMMON_H)
	@$(MAKE) -C ../common txt

../common/obj_all/mini%.o: ../common/%.c $(COMMON_H)
	@$(MAKE) -C ../common txt
