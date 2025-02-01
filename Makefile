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

LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lncurses

ifeq ($(filter debug, $(MAKECMDGOALS)),)
else
BUILD_DIR ?= ./.build/debug
endif

ifeq ($(MAKECMDGOALS), release)
BUILD_DIR ?= ./.build/release
endif

BUILD_DIR ?= ./.build

BUILD_BIN := $(BUILD_DIR)/$(BIN)

OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=%.d)

-include $(DEP)

.PHONY: all
all:
	@$(MAKE) release

$(BUILD_BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) $^ -o $@

.PHONY: $(BIN)
$(BIN): $(BUILD_BIN)
	cp $(BUILD_BIN) $(BIN)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -c $< -o $@

.PHONY: release
release: BUILD_DIR += /release
release: CFLAGS ?= -O3 -march=native -Wall -Wextra -std=c++20
release: ${BIN}


.PHONY: debug
debug: BUILD_DIR += /debug
debug: CFLAGS ?= -O0 -g3 -Wall -Wextra -std=c++20 \
    -fsanitize=address,undefined,leak -fno-omit-frame-pointer
debug: CPPFLAGS += -DDEBUG
debug: ${BIN}

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(BIN)

.PHONY: re
re: fclean
	$(MAKE) release
