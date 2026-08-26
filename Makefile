# libsa Makefile
LIBNAME = sa
VERSION = 1.0
PREFIX = /usr

INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

CFLAGS = -fPIC -Wall -Wextra -O2 -I$(INCLUDE_DIR)
LDFLAGS = -shared -Wl,-soname,lib$(LIBNAME).so.1

LIB_FILE = lib$(LIBNAME).so.$(VERSION)
SONAME = lib$(LIBNAME).so.1
LIB_LINK = lib$(LIBNAME).so

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR)/$(LIB_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(LIB_FILE): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	ln -sf $(LIB_FILE) $(BUILD_DIR)/$(SONAME)
	ln -sf $(SONAME) $(BUILD_DIR)/$(LIB_LINK)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	install -m 755 $(BUILD_DIR)/$(LIB_FILE) $(DESTDIR)$(PREFIX)/lib/
	ln -sf $(LIB_FILE) $(DESTDIR)$(PREFIX)/lib/$(SONAME)
	ln -sf $(SONAME) $(DESTDIR)$(PREFIX)/lib/$(LIB_LINK)
	install -m 644 $(INCLUDE_DIR)/sa.h $(DESTDIR)$(PREFIX)/include/

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all install clean
