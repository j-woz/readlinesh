
# Makefile rules for building distributions

DEB_LIST = debian/list.mk

include version.mk
include $(DEB_LIST)

deb: readlinesh_$(VERSION)-1_amd64.deb

DEB_FILE_PATHS = $(patsubst %,debian/%,$(DEB_FILES))

ORIG_FILES = $(SRCS) $(HEADERS) Makefile.in configure.ac configure \
	$(DEB_FILE_PATHS) docs/readline.1

readlinesh_$(VERSION).orig.tar.gz: $(ORIG_FILES) $(DEB_LIST)
	maint/mk-upstream-tgz.sh $(@) $(VERSION) $(ORIG_FILES)

readlinesh_$(VERSION)-1_amd64.deb: readlinesh_$(VERSION).orig.tar.gz
	maint/mk-debian.sh $(@) $(<) $(VERSION)
