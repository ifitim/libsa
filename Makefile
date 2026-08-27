CC=gcc
CFLAGS=-fPIC -Iinclude
LDFLAGS=-L. -lsa

all:
	$(CC) $(CFLAGS) -shared src/sa.c -o libsa.so

test:
	$(CC) $(CFLAGS) test.c $(LDFLAGS) -o test
install:
	mkdir -p $(DESTDIR)/usr/lib
	mkdir -p $(DESTDIR)/usr/include

	cp libsa.so $(DESTDIR)/usr/lib/libsa.so.1.0
	ln -sf libsa.so.1.0 $(DESTDIR)/usr/lib/libsa.so.1
	ln -sf libsa.so.1.0 $(DESTDIR)/usr/lib/libsa.so

	cp include/sa.h $(DESTDIR)/usr/include/
clean:
	rm -f libsa.so test
