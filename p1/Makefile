# Root 15410 Makefile
# Do not edit this file

#################### RULE HEADER ####################
.PHONY: update query_update print html_doc
all: query_update bootfd.img

############## VARIABLE DEFINITIONS #################

DOC = doxygen
MAKE = gmake
CC = gcc
LD = ld
AR = ar
OBJCOPY = objcopy

AFS_DIR = /afs/cs.cmu.edu/academic/class/15410-f06/Web/update

PROJROOT = $(PWD)
# All paths relative to PROJROOT unless otherwise noted
410KDIR = 410kern
410UDIR = 410user
STUKDIR = kern
STUUDIR = user
BUILDDIR = temp

# These need to be known before we run includes, sadly
410KLIBDIR = $(410KDIR)/lib
410ULIBDIR = $(410UDIR)/lib
STUULIBDIR = $(STUUDIR)/lib

# Relative to {410,STU}UDIR
UPROGDIR = progs

################ CONFIGURATION INCLUSION #################

include config.mk

############### TARGET VARIABLES ###############

PROGS = $(410REQPROGS) $(STUDENTREQPROGS) $(410TESTS) $(STUDENTTESTS)

410ULIBS = $(patsubst %,$(410ULIBDIR)/%,$(410USER_LIBS))
STUULIBS = $(patsubst %,$(STUULIBDIR)/%,$(STUDENT_LIBS))

################# MISCELLANEOUS VARAIBLES ##############

MTOOLSRC=$(PROJROOT)/mtools.conf

CRT0 = $(410UDIR)/$(UPROGDIR)/crt0.o

LDFLAGSENTRY = --entry=_main

########### MAKEFILE FILE INCLUSION ##############

# These are optional so that we can use the same Makefile for P1,2,3

# Include 410kern control, responsible for 410kern libraries, objects, interim
-include $(410KDIR)/kernel.mk
# Include 410user control, responsible for 410user libraries and programs
-include $(410UDIR)/user.mk
# Include stukern control, responsible for stukern objects, interim
-include $(STUKDIR)/kernel.mk
# Include stuuser control, responsible for 410user libraries and programs
-include $(STUUDIR)/user.mk

############# BUILD PARAMETER VARIABLES ################
# Note that this section DEPENDS UPON THE INCLUDES ABOVE
KCFLAGS = -nostdinc -fno-stack-protector -fno-strict-aliasing -fno-builtin -Wall -gstabs -O0 -m32
KLDFLAGS = -static -Ttext 100000 -melf_i386
KINCLUDES = -I$(410KDIR)/inc -I$(410KLIBDIR)/inc -I$(STUKDIR)/inc
UCFLAGS = -nostdinc -fno-strict-aliasing -fno-builtin -Wall -gstabs -O0 -m32
ULDFLAGS = -static -Ttext 1000000 --fatal-warnings -melf_i386 $(LDFLAGSENTRY)
UINCLUDES = -I$(410UDIR)/inc -I$(410ULIBDIR)/inc \
						-I$(STUUDIR)/inc -I$(STUULIBDIR)/inc

############## UPDATE RULES #####################

update:
	./update.sh $(UPDATE_METHOD)

query_update:
	./update.sh $(UPDATE_METHOD) query

################### GENERIC RULES ######################
%.dep: %.S
	$(CC) $(CFLAGS) -DASSEMBLER $(INCLUDES) -M -MP -MF $@ -MT $(<:.S=.o) $<

%.dep: %.s
	@echo "You should use the .S file extension rather than .s"
	@echo ".s does not support precompiler directives (like #include)"
	@false

%.dep: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -M -MP -MF $@ -MT $(<:.c=.o) $<

%.o: %.S
	$(CC) $(CFLAGS) -DASSEMBLER $(INCLUDES) -c -o $@ $<
	$(OBJCOPY) -R .comment -R .note $@ $@

%.o: %.s
	@echo "You should use the .S file extension rather than .s"
	@echo ".s does not support precompiler directives (like #include)"
	@false

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	$(OBJCOPY) -R .comment -R .note $@ $@

%.a:
	$(AR) rc $@ $^

################ PATTERNED VARIABLE ASSIGNMENTS ##################
$(410KDIR)/%: CFLAGS=$(KCFLAGS)
$(410KDIR)/%: INCLUDES=$(KINCLUDES)
$(410KDIR)/%: LDFLAGS=$(KLDFLAGS)
$(STUKDIR)/%: CFLAGS=$(KCFLAGS)
$(STUKDIR)/%: INCLUDES=$(KINCLUDES)
$(STUKDIR)/%: LDFLAGS=$(KLDFLAGS)
$(410UDIR)/%: CFLAGS=$(UCFLAGS)
$(410UDIR)/%: INCLUDES=$(UINCLUDES)
$(410UDIR)/%: LDFLAGS=$(ULDFLAGS)
$(STUUDIR)/%: CFLAGS=$(UCFLAGS)
$(STUUDIR)/%: INCLUDES=$(UINCLUDES)
$(STUUDIR)/%: LDFLAGS=$(ULDFLAGS)

################# USERLAND PROGRAM UNIFICATION RULES #################

$(410REQPROGS:%=$(BUILDDIR)/%): $(BUILDDIR)/%: $(410UDIR)/$(UPROGDIR)/%
	mkdir -p $(BUILDDIR)
	cp $< $@

$(410TESTS:%=$(BUILDDIR)/%) : $(BUILDDIR)/% : $(410UDIR)/$(UPROGDIR)/%
	mkdir -p $(BUILDDIR)
	cp $< $@

$(STUDENTREQPROGS:%=$(BUILDDIR)/%) : $(BUILDDIR)/% : $(STUUDIR)/$(UPROGDIR)/%
	mkdir -p $(BUILDDIR)
	cp $< $@

$(STUDENTTESTS:%=$(BUILDDIR)/%) : $(BUILDDIR)/% : $(STUUDIR)/$(UPROGDIR)/%
	mkdir -p $(BUILDDIR)
	cp $< $@

############## MISCELLANEOUS TARGETS #################

html_doc:
	$(DOC) doxygen.conf

print:
	enscript -2r -p kernel.ps README.dox \
		`find ./kern/ -type f -regex  '.*\.[chS]' | sort`

################# CLEANING RULES #####################
.PHONY: clean veryclean

clean:
	rm -f $(MTOOLSRC) $(CRT0)
	rm -f $(FINALCLEANS)
	rm -f $(ALL_410KOBJS)
	rm -f $(ALL_410KOBJS:%.o=%.dep)
	rm -f $(410KCLEANS)
	rm -f $(ALL_410UOBJS)
	rm -f $(ALL_410UOBJS:%.o=%.dep)
	rm -f $(410UCLEANS)
	rm -f $(410UPROGS:%=%.o)
	rm -f $(ALL_STUKOBJS)
	rm -f $(ALL_STUKOBJS:%.o=%.dep)
	rm -f $(STUKCLEANS)
	rm -f $(ALL_STUUOBJS)
	rm -f $(ALL_STUUOBJS:%.o=%.dep)
	rm -f $(STUUCLEANS)
	rm -f $(STUUPROGS:%=%.o)

veryclean: clean
	rm -rf doc kernel.ps bootfd.img kernel $(BUILDDIR)
	rm -f $(FINALVERYCLEANS)

%clean:
	$(error "Unknown cleaning target")

########### DEPENDENCY FILE INCLUSION ############
ifeq (0,$(words $(filter %clean,$(MAKECMDGOALS))))
ifneq (,$(ALL_410KOBJS))
-include $(ALL_410KOBJS:.o=.dep)
endif
ifneq (,$(ALL_STUKOBJS))
-include $(ALL_STUKOBJS:.o=.dep)
endif
ifneq (,$(ALL_410UOBJS))
-include $(ALL_410UOBJS:.o=.dep)
endif
ifneq (,$(ALL_STUUOBJS))
-include $(ALL_STUUOBJS:.o=.dep)
endif
endif

########### MANDATE CLEANING AS ONLY TARGETS ############
ifneq (0,$(words $(filter %clean,$(MAKECMDGOALS))))
  # The target includes a make target
  ifneq (0, $(words $(filter-out %clean,$(MAKECMDGOALS))))
    # There is another target on the list
    $(error "Clean targets must run by themselves")
  endif
endif
