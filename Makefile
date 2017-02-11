all :
	$(MAKE) -C lib
	$(MAKE) -C headers
	$(MAKE) -C src
	$(MAKE) -C analyse

clean :
	$(MAKE) -C lib clean
	$(MAKE) -C headers clean
	$(MAKE) -C src clean
	$(MAKE) -C analyse clean
