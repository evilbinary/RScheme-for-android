# This is the preamble.mak used when building packages and other addons
# INSTALL_DIR=/data/data/org.evilbinary.cl/system/rs
IFLAGS=$(USR_IFLAGS) -I. $(SYS_IFLAGS) -I$(INSTALL_DIR)/include
SUBPROJ_LD=ld
SUBPROJ_LD_FLAGS=-r
LDX_FLAGS=-L$(INSTALL_DIR)/lib -lrs -rdynamic -lm -ldl
CC=gcc
CFLAGS1=-DANDROID -g -O -DNDEBUG -DINLINES -DGC_MACROS -Wall -Wno-unused
CFLAGS=$(CFLAGS1) $(XCFLAGS) $(IFLAGS)
