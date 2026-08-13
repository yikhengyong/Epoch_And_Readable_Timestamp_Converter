# Compiler and Flags
CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -std=c11 -Iinclude -MMD -MP
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build

# Detect OS
ifeq ($(OS),Windows_NT)
    SHELL       := cmd.exe
    EXE         := .exe
    TARGET      := $(BUILD_DIR)/main$(EXE)
    MKDIR_BUILD := if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
    MKDIR_SRC   := if not exist "$(BUILD_DIR)\$(SRC_DIR)" mkdir "$(BUILD_DIR)\$(SRC_DIR)"
    RM          := if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
    RUN_CMD     := $(BUILD_DIR)\main.exe
else
    EXE         :=
    TARGET      := $(BUILD_DIR)/main
    MKDIR_BUILD := mkdir -p $(BUILD_DIR)
    MKDIR_SRC   := mkdir -p $(BUILD_DIR)/$(SRC_DIR)
    RM          := rm -rf $(BUILD_DIR)
    RUN_CMD     := ./$(TARGET)
endif

# Source & Object Files
SRCS      := main.c $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)

.PHONY: all clean run test

# Build target
all: clean $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile root main.c
$(BUILD_DIR)/main.o: main.c
	@$(MKDIR_BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile src/*.c files
$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Include auto-generated dependency rules
-include $(DEPS)

# Run target
run: $(TARGET)
	@echo --- Running Target ---
	@$(RUN_CMD)

test: run

# Clean build directory
clean:
	@$(RM)
