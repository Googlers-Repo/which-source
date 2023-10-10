CXXFLAGS += -pie -Wall -Wextra -Werror -std=c++14 -fno-exceptions -Wno-unused-variable
PREFIX ?= /usr/local

which: which.cpp

clean:
	rm -f which

install: which
	install which $(DESTDIR)$(PREFIX)/bin/which

uninstall:
	rm -f $(PREFIX)/bin/which

.PHONY: clean install uninstall