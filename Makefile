#--- Learn digits ---#

### User-defined variables ###
IS_DEBUG ?= 0
NAME = game
SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include

### Variables ###
CC = gcc
TESTS_FLAGS := -std=c99 -pedantic -Wall -Wextra -Werror \
               -Og -g -ggdb
RELEASE_FLAGS := -O3 -march=native
LDFLAGS += -flto

BUILD_DIR_ROOT := $(BUILD_DIR)
ifeq ($(IS_DEBUG), 0)
    BUILD_DIR := $(BUILD_DIR)/release
else
    BUILD_DIR := $(BUILD_DIR)/debug
endif

TARGET := $(BUILD_DIR)/$(NAME)

ifeq ($(IS_DEBUG), 0)
	CFLAGS += $(RELEASE_FLAGS)
else
    CFLAGS += $(TESTS_FLAGS)
    LD_PRELOAD += -fsanitize=address
endif

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

INCLUDE_DIRECTORIES := $(shell find $(SRC_DIR) -type d) $(INCLUDE_DIR)
INCLUDE_FLAGS := $(addprefix -I,$(INCLUDE_DIRECTORIES))

CFLAGS += $(INCLUDE_FLAGS) -MMD -MP

### Rules ###

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	@./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR_ROOT)

.PHONY: fmt
fmt: $(SRCS) $(HEADERS)
	@clang-format -i $^

.PHONY: lint
lint: $(SRCS) $(HEADERS)
	@splint $(SRCS) $(HEADERS)


### Include the .d generated Makefiles ###
-include $(DEPS)
