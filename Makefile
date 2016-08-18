recall : main.c main.h commands.h
	cc -std=c99 -g -Wall -Wpedantic -o recall main.c

install:
	@mkdir -p $(DESTDIR)/$(PREFIX)/bin
	@cp recall $(DESTDIR)/$(PREFIX)/bin

clean:
	@rm recall
