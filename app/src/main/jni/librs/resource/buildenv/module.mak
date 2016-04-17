OFILES=$(CFILES:.c=.o)
SOFILES=$(CFILES:.c=.so)
# INSTALL_DIR=/data/data/org.evilbinary.cl/system/rs
include $(INSTALL_DIR)/resource/buildenv/preamble.mak

LD=ld
LD_FLAGS=-r

$(PRODUCT): $(OFILES)
	$(LD) $(LD_FLAGS) $(OFILES) -o $(PRODUCT)

clean::
	rm -f $(PRODUCT) $(OFILES) $(SOFILES)

$(INSTALL_DIR)/include/rscheme/pkgs:
	mkdir $(INSTALL_DIR)/include/rscheme/pkgs

install:: $(PRODUCT) $(INSTALL_DIR)/include/rscheme/pkgs
	cp $(PRODUCT) $(INSTALL_DIR)/lib
	cp $(INCFILES) $(INSTALL_DIR)/include/rscheme/pkgs
	cp $(MIFBASEFILE).mif $(INSTALL_DIR)/resource/modules
	cp $(MIFBASEFILE).mx $(INSTALL_DIR)/resource/modules

SO_PRODUCT=lib$(PRODUCT:.o=.so)
$(SO_PRODUCT): $(SOFILES)
	$(CC) -shared $(SOFILES) -o $(SO_PRODUCT) $(XLFLAGS)

%.so: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -fPIC -o $@ $^

install.so: $(SO_PRODUCT)
	cp $(SO_PRODUCT) $(INSTALL_DIR)/resource/modules
	cp $(INCFILES) $(INSTALL_DIR)/include/rscheme/pkgs
	cp $(MIFBASEFILE).mif $(INSTALL_DIR)/resource/modules
	cp $(MIFBASEFILE).mx $(INSTALL_DIR)/resource/modules
