410KLIB_DEBUG_OBJS := $(410KLIBDIR)/kerndebug/kerndebug.o

ALL_410KOBJS += $(410KLIB_DEBUG_OBJS)
410KCLEANS += $(410KLIBDIR)/libkerndebug.a

$(410KLIBDIR)/libkerndebug.a: $(410KLIB_DEBUG_OBJS)
