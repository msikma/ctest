TITLE = CGA Test
SLUG = cga_test
COPYRIGHT = (C) 2024, MIT license
URL = https://github.com/msikma/cgatest

CC = wcl
SRC_DIR = src
DIST_DIR = dist
TEST_DIR = bintest
STATIC_DIR = static

BIN = $(SLUG).exe

DOSBOX = dosbox
CONFIG = resources/dosbox.conf

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst %.c, %.o, $(SRCS))
DIST_BIN = $(DIST_DIR)/$(SLUG)/$(BIN)
CFLAGS = -ox -ot -q -0 -we

STATIC_FILES = $(wildcard $(STATIC_DIR)/*)
DIST_FILES = $(patsubst $(STATIC_DIR)/%, $(DIST_DIR)/$(SLUG)/%, $(STATIC_FILES))

HASH = $(shell git rev-parse --short HEAD | tr [:lower:] [:upper:])
BRANCH = $(shell git symbolic-ref -q --short HEAD || git rev-parse --short HEAD)
COUNT = $(shell git rev-list HEAD --count)
VERSION = $(BRANCH)-$(COUNT) [$(HASH)]
DATE = $(shell date +"%Y-%m-%d")

ZIP_DIST = $(DIST_DIR)/$(SLUG).zip
ZIP_FILE = $(SLUG)-$(BRANCH)-$(COUNT).zip

DIRS = $(DIST_DIR)/$(SLUG) $(DIST_DIR) $(TEST_DIR)

# The branch file changes on commit; this is used to regenerate bin.h.
BRANCH_FILE = $(shell git rev-parse --git-path refs/heads/$(BRANCH))

# Check if the Open Watcom compiler is available.
ifeq (, $(shell which $(CC)))
  $(error The Open Watcom compiler is not installed)
endif

all: game
default: game

$(DIRS):
	mkdir -p $@

$(DIST_FILES): $(STATIC_FILES) | $(DIST_DIR)
	cp $< $@

$(SRC_DIR)/util/bin.c: $(SRC_DIR)/util/bin.h

$(SRC_DIR)/util/bin.h: $(BRANCH_FILE)
	sed -e "s|%%GIT_HASH%%|$(HASH)|g" -e "s|%%GIT_BRANCH%%|$(BRANCH)|g" -e "s|%%GIT_COUNT%%|$(COUNT)|g" -e "s|%%GIT_VERSION%%|$(VERSION)|g" -e "s|%%GIT_DATE%%|$(DATE)|g" -e "s|%%BIN%%|$(BIN)|g" $(SRC_DIR)/util/bin_tpl.h > $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -bt=dos -c -fo=$@ $<

$(DIST_BIN): $(OBJS) | $(DIST_DIR)/$(SLUG)
	$(CC) $(CFLAGS) -bcl=dos -fe=$(DIST_BIN) $(OBJS)

$(TEST_DIR)/dosbox.conf: $(TEST_DIR)
	sed -e "s|%%TEST_DIR%%|$(TEST_DIR)|g" -e "s|%%LOG_FILE%%|log_$(shell date +%Y%m%d_%H%M%S).txt|g" -e "s|%%EXEC%%|$(BIN)|g" $(CONFIG) > $(TEST_DIR)/dosbox.conf

$(TEST_DIR)/$(BIN): $(DIST_BIN) | $(TEST_DIR)
	cp $(DIST_BIN) $(TEST_DIR)/$(BIN)

$(ZIP_DIST): game
	pushd $(DIST_DIR); zip -r -9 -T -o -v $(ZIP_FILE) $(SLUG)

zip: $(ZIP_DIST)

test: $(TEST_DIR)/$(BIN) $(TEST_DIR)/dosbox.conf
	$(DOSBOX) -conf $(TEST_DIR)/dosbox.conf 2>/dev/null

game: $(DIST_DIR)/$(SLUG) $(DIST_BIN) $(DIST_FILES)

clean:
	rm -rf $(DIRS) $(OBJS) $(SRC_DIR)/util/bin.h

.PHONY: clean game test zip
