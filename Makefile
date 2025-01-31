##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## make file should make the files
##

BIN ?= MyGKrellm

CPPFLAGS += -I./include

CC := g++

SRC := $(shell find src/ -name "*.cpp")

TESTS_SRC := $(shell find tests/ -name "*.cpp")
TESTS_SRC += $(filter-out src/main.cpp,$(SRC))

ifeq ($(filter debug run, $(MAKECMDGOALS)),)
else
BUILD_DIR ?= ./.build/debug
endif

ifeq ($(filter tests_run tests_bin, $(MAKECMDGOALS)),)
else
BUILD_DIR ?= ./.build/tests
endif

ifeq ($(MAKECMDGOALS), release)
BUILD_DIR ?= ./.build/release
endif

BUILD_DIR ?= ./.build

BUILD_BIN := $(BUILD_DIR)/$(BIN)

HEADERS := $(shell find include/ -name "*.hpp")

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=%.d)

TESTS_OBJ := $(TESTS_SRC:%.c=$(BUILD_DIR)/%.o)

.PHONY: all
all:
	@$(MAKE) release

$(BUILD_BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@

.PHONY: $(BIN)
$(BIN): $(BUILD_BIN)
	cp $(BUILD_BIN) $(BIN)

-include $(DEP)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@

.PHONY: release
release: BUILD_DIR += /release
release: CFLAGS ?= -O3 -march=native -Wall -Wextra -Werror -std=c++20
release: ${BIN}


.PHONY: debug
debug: BUILD_DIR += /debug
debug: CFLAGS ?= -O0 -g3 -Wall -Wextra -std=c++20 \
    -fsanitize=address,undefined,leak,integer -fno-omit-frame-pointer
debug: CPPFLAGS += -DDEBUG
debug: ${BIN}

tests_bin: $(TESTS_OBJ)
	$(CC) $(TESTS_OBJ) $(CFLAGS) -o tests_bin $(LDFLAGS)

.PHONY: tests_run
tests_run:LDFLAGS+=-lcriterion
tests_run: tests_bin
	./tests_bin

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(BIN)

.PHONY: re
re: fclean
	$(MAKE) release
