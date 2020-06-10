PKGCONFIG ?= pkgconf
ifeq (, $(shell command -v pkgconf))
PKGCONFIG ?= pkg-config
endif
DEFINITIONS= PKGCONFIG=$(PKGCONFIG)

all :
	$(MAKE) -C lib $(DEFINITIONS)
	$(MAKE) -C headers $(DEFINITIONS)
	$(MAKE) -C src $(DEFINITIONS)
	$(MAKE) -C test $(DEFINITIONS)
	$(MAKE) -C analyse $(DEFINITIONS)

clean :
	$(MAKE) -C lib clean
	$(MAKE) -C headers clean
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(MAKE) -C analyse clean
