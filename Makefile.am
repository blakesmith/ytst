SUBDIRS=src
ACLOCAL_AMFLAGS = -I m4

clean-local:
	rm -rf aclocal.m4 autom4te.cache compile configure config config.h config.h.in config.log config.status depcomp install-sh missing stamp-h1 Makefile Makefile.in src/Makefile.in test/Makefile.in

pkg: all
	sudo checkinstall --pkgname=$(PACKAGE) \
			  --pkgversion=$(VERSION) \
			  --default

if BUILDING_DEB
DEBSOURCEPKG=$(PACKAGE)_$(VERSION).orig.tar.gz
DEBSOURCEDIR=$(PACKAGE)-$(VERSION)
deb: dist
	@$(ECHO) "Building Debian package..."; \
	if $(TEST) ! -d debian; then \
		$(ECHO) "The files needed for building a Debian package are not" \
		"included by default in the distribution. To build a package, check" \
		"out the project from source control."; \
		exit 1; \
	fi; \
	$(MV) $(PACKAGE)-$(VERSION).tar.gz $(DEBSOURCEPKG) && \
	$(TAR) --extract --gunzip --file $(DEBSOURCEPKG) && \
	$(MKDIR_P) $(DEBSOURCEDIR)/debian && \
	$(CP) \
		debian/changelog \
		debian/compat \
		debian/control \
		debian/copyright \
		debian/docs \
		debian/rules \
		$(DEBSOURCEDIR)/debian && \
	cd $(DEBSOURCEDIR) && \
	$(DEBUILD) -rfakeroot -D -us -uc; \
	cd $(srcdir); \
	rm --force $(DEBSOURCEPKG); \
	rm --recursive --force $(DEBSOURCEDIR)
else
deb:
	@$(ECHO) \
	"To build a Debian package, you must run configure with --enable-deb."; \
	exit 1
endif

