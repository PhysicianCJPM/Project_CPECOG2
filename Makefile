# Makefile for Intelligent Process Scheduler

CC = gcc
CFLAGS = -Wall -Wextra -O2
SRC_DIR = src
OBJ_DIR = obj
BIN = scheduler

# Source files and corresponding object files
SOURCES = $(SRC_DIR)/scheduler.c $(SRC_DIR)/process_management.c $(SRC_DIR)/metrics.c $(SRC_DIR)/ann_inference.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN)
