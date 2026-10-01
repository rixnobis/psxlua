# Makefile for building Lua
# See ../doc/readme.html for installation and customization instructions.

# == CHANGE THE SETTINGS BELOW TO SUIT YOUR ENVIRONMENT =======================

# Your platform. See PLATS for possible values.
PLAT= none

ifneq ($(TARGET),psx)
CC= gcc
CFLAGS= -m32 -O2 -Wall -DLUA_COMPAT_ALL $(SYSCFLAGS) $(MYCFLAGS)
LDFLAGS= -m32 $(SYSLDFLAGS) $(MYLDFLAGS)
LIBS= -lm $(SYSLIBS) $(MYLIBS)
AR= ar rcu
RANLIB= ranlib
else
ifeq ($(OS),Windows_NT)
HAS_LINUX_MIPS_GCC = false
else
HAS_LINUX_MIPS_GCC = $(shell which mipsel-linux-gnu-gcc > /dev/null 2> /dev/null && echo true || echo false)
endif

ifeq ($(HAS_LINUX_MIPS_GCC),true)
PREFIX ?= mipsel-linux-gnu
else
PREFIX ?= mipsel-none-elf
endif
ARCHFLAGS = -march=mips1 -mabi=32 -EL -fno-pic -mno-shared -mno-abicalls -mfp32 -mno-llsc
ARCHFLAGS += -fno-stack-protector -nostdlib -ffreestanding
CPPFLAGS = -Wall -DLUA_COMPAT_ALL -DLUA_TARGET_PSX
CPPFLAGS += -ffunction-sections
CPPFLAGS += -fdata-sections -mno-gpopt -fomit-frame-pointer
CPPFLAGS += -fno-builtin -fno-strict-aliasing -Wno-attributes
CPPFLAGS += $(ARCHFLAGS)
CPPFLAGS += -Os -g
CC = $(PREFIX)-gcc
CXX = $(PREFIX)-g++
AR = $(PREFIX)-gcc-ar rcu
RANLIB = $(PREFIX)-ranlib
LIBS=
endif

RM= rm -f

SYSCFLAGS=
SYSLDFLAGS=
SYSLIBS=

MYCFLAGS=
MYLDFLAGS=
MYLIBS=
MYOBJS=

# == END OF USER SETTINGS -- NO NEED TO CHANGE ANYTHING BELOW THIS LINE =======

PLATS= host32 psx psx-noparser psx-luac

ifeq ($(NOPARSER),true)
LUA_A=	liblua-noparser.a
else
LUA_A=	liblua.a
endif
CORE_O=	lapi.o lctype.o ldebug.o ldo.o lfunc.o lgc.o \
	lmem.o lobject.o lopcodes.o lstate.o lstring.o ltable.o \
	ltm.o lundump.o lvm.o lzio.o llibc.o
ifeq ($(NOPARSER),true)
PARSER_O=	lnoparser.o
else
PARSER_O=	lcode.o ldump.o llex.o lparser.o
endif
LIB_O=	lauxlib.o lbaselib.o lbitlib.o lcorolib.o ldblib.o \
	lstrlib.o ltablib.o linit.o
BASE_O= $(CORE_O) $(PARSER_O) $(LIB_O) $(MYOBJS)

LUA_T=	lua
LUA_O=	lua.o

LUAC_T=	luac
LUAC_O=	luac.o

ALL_O= $(BASE_O) $(LUA_O)
ALL_T= $(LUA_A) $(LUA_T)
ALL_A= $(LUA_A)

# Targets start here.
default: $(PLAT)

all:	$(ALL_T)

o:	$(ALL_O)

a:	$(ALL_A)

$(LUA_A): $(BASE_O)
	$(AR) $@ $(BASE_O)
	$(RANLIB) $@

$(LUA_T): $(LUA_O) $(LUA_A)
	$(CC) -o $@ $(LDFLAGS) $(LUA_O) $(LUA_A) $(LIBS)

clean:
	$(RM) $(ALL_T) $(ALL_O) $(ALL_A) liblua-noparser.a lnoparser.o
	$(RM) $(LUAC_T) $(LUAC_O) psx-heap.o psx-glue.o luac.elf luac.map luac.ps-exe *.dep

depend:
	@$(CC) $(CFLAGS) -MM l*.c

echo:
	@echo "PLAT= $(PLAT)"
	@echo "CC= $(CC)"
	@echo "CFLAGS= $(CFLAGS)"
	@echo "LDFLAGS= $(SYSLDFLAGS)"
	@echo "LIBS= $(LIBS)"
	@echo "AR= $(AR)"
	@echo "RANLIB= $(RANLIB)"
	@echo "RM= $(RM)"

# Convenience targets for popular platforms
ALL= all

none:
	@echo "Please do 'make PLATFORM' where PLATFORM is one of these:"
	@echo "   $(PLATS)"

host32: $(ALL)

psx:
	$(MAKE) a TARGET=psx

psx-noparser:
	$(MAKE) a TARGET=psx NOPARSER=true

psx-luac: psx
	$(MAKE) -f luac-psx.mk

# list targets that do not create files (but not all makes understand .PHONY)
.PHONY: all $(PLATS) default o a clean depend echo none

# DO NOT DELETE

lapi.o: lapi.c lua.h luaconf.h lapi.h llimits.h lstate.h lobject.h ltm.h \
 lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h lstring.h ltable.h lundump.h \
 lvm.h
lauxlib.o: lauxlib.c lua.h luaconf.h lauxlib.h llibc.h
lbaselib.o: lbaselib.c lua.h luaconf.h lauxlib.h lualib.h lctype.h llibc.h
lbitlib.o: lbitlib.c lua.h luaconf.h lauxlib.h lualib.h
lcode.o: lcode.c lua.h luaconf.h lcode.h llex.h lobject.h llimits.h \
 lzio.h lmem.h lopcodes.h lparser.h ldebug.h lstate.h ltm.h ldo.h lgc.h \
 lstring.h ltable.h lvm.h
lcorolib.o: lcorolib.c lua.h luaconf.h lauxlib.h lualib.h
lctype.o: lctype.c lctype.h lua.h luaconf.h llimits.h
ldblib.o: ldblib.c lua.h luaconf.h lauxlib.h lualib.h llibc.h
ldebug.o: ldebug.c lua.h luaconf.h lapi.h llimits.h lstate.h lobject.h \
 ltm.h lzio.h lmem.h lcode.h llex.h lopcodes.h lparser.h ldebug.h ldo.h \
 lfunc.h lstring.h lgc.h ltable.h lvm.h llibc.h
ldo.o: ldo.c lua.h luaconf.h lapi.h llimits.h lstate.h lobject.h ltm.h \
 lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h lopcodes.h lparser.h \
 lstring.h ltable.h lundump.h lvm.h llibc.h
ldump.o: ldump.c lua.h luaconf.h lobject.h llimits.h lstate.h ltm.h \
 lzio.h lmem.h lundump.h
lfunc.o: lfunc.c lua.h luaconf.h lfunc.h lobject.h llimits.h lgc.h \
 lstate.h ltm.h lzio.h lmem.h
lgc.o: lgc.c lua.h luaconf.h ldebug.h lstate.h lobject.h llimits.h ltm.h \
 lzio.h lmem.h ldo.h lfunc.h lgc.h lstring.h ltable.h llibc.h
linit.o: linit.c lua.h luaconf.h lualib.h lauxlib.h
liolib.o: liolib.c lua.h luaconf.h lauxlib.h lualib.h
llex.o: llex.c lua.h luaconf.h lctype.h llimits.h ldo.h lobject.h \
 lstate.h ltm.h lzio.h lmem.h llex.h lparser.h lstring.h lgc.h ltable.h llibc.h
lmathlib.o: lmathlib.c lua.h luaconf.h lauxlib.h lualib.h
lmem.o: lmem.c lua.h luaconf.h ldebug.h lstate.h lobject.h llimits.h \
 ltm.h lzio.h lmem.h ldo.h lgc.h
loadlib.o: loadlib.c lua.h luaconf.h lauxlib.h lualib.h
lobject.o: lobject.c lua.h luaconf.h lctype.h llimits.h ldebug.h lstate.h \
 lobject.h ltm.h lzio.h lmem.h ldo.h lstring.h lgc.h lvm.h llibc.h
lopcodes.o: lopcodes.c lopcodes.h llimits.h lua.h luaconf.h
loslib.o: loslib.c lua.h luaconf.h lauxlib.h lualib.h
lparser.o: lparser.c lua.h luaconf.h lcode.h llex.h lobject.h llimits.h \
 lzio.h lmem.h lopcodes.h lparser.h ldebug.h lstate.h ltm.h ldo.h lfunc.h \
 lstring.h lgc.h ltable.h
lstate.o: lstate.c lua.h luaconf.h lapi.h llimits.h lstate.h lobject.h \
 ltm.h lzio.h lmem.h ldebug.h ldo.h lfunc.h lgc.h llex.h lstring.h \
 ltable.h llibc.h
lstring.o: lstring.c lua.h luaconf.h lmem.h llimits.h lobject.h lstate.h \
 ltm.h lzio.h lstring.h lgc.h llibc.h
lstrlib.o: lstrlib.c lua.h luaconf.h lauxlib.h lualib.h lctype.h llibc.h
ltable.o: ltable.c lua.h luaconf.h ldebug.h lstate.h lobject.h llimits.h \
 ltm.h lzio.h lmem.h ldo.h lgc.h lstring.h ltable.h lvm.h
ltablib.o: ltablib.c lua.h luaconf.h lauxlib.h lualib.h
ltm.o: ltm.c lua.h luaconf.h lobject.h llimits.h lstate.h ltm.h lzio.h \
 lmem.h lstring.h lgc.h ltable.h
lua.o: lua.c lua.h luaconf.h lauxlib.h lualib.h
luac.o: luac.c lua.h luaconf.h lauxlib.h lobject.h llimits.h lstate.h \
 ltm.h lzio.h lmem.h lundump.h ldebug.h lopcodes.h
lundump.o: lundump.c lua.h luaconf.h ldebug.h lstate.h lobject.h \
 llimits.h ltm.h lzio.h lmem.h ldo.h lfunc.h lstring.h lgc.h lundump.h llibc.h
lvm.o: lvm.c lua.h luaconf.h ldebug.h lstate.h lobject.h llimits.h ltm.h \
 lzio.h lmem.h ldo.h lfunc.h lgc.h lopcodes.h lstring.h ltable.h lvm.h llibc.h
lzio.o: lzio.c lua.h luaconf.h llimits.h lmem.h lstate.h lobject.h ltm.h \
 lzio.h llibc.h
lnoparser.o: lnoparser.c lua.h luaconf.h llex.h lobject.h \
 llimits.h lzio.h lmem.h lparser.h lundump.h
llibc.o: llibc.c llibc.h
