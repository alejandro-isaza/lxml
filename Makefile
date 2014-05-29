.PHONY: all

all:
	@$(MAKE) -C src $@

test:
	@$(MAKE) -C tests $@

doc: Doxyfile src/*.h
	@doxygen

.DEFAULT:
	@$(MAKE) -C src $@
	@$(MAKE) -C tests $@
