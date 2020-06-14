CC=gcc
CFLAGS=-O3 -Wall -Wextra
LDFLAGS = -fpie -Wl,-pie 

SRC_DIR := src
OBJ_DIR := build
OUT_DIR := $(OBJ_DIR)/out
TARGET := $(OUT_DIR)/main

INC_FOLDER = include
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: directories $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_FOLDER) -c -o $@ $<

.PHONY: clean
clean: 
	rm -f $(OBJ_FILES) $(TARGET)
	rmdir $(OUT_DIR) $(OBJ_DIR)

MKDIR_P = mkdir -p

.PHONY: directories
directories: ${OUT_DIR}
${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

test: all
	./test.sh $(TARGET)
