# CC = gcc
# LDLIBS = -lraylib
# CFLAGS = -g -Wall -ggdb3 -std=c++20 
# GAME_SRC_DIR = /src
# GAME_LIB_DIR = /include

# LIB = $(shell find $(ENGINE_LIB_DIR) -name '*.h') $(shell find $(GAME_LIB_DIR) -name '*.h')
# ENGINE_SRC := $(shell find $(ENGINE_SRC_DIR) -name '*.cpp')
# GAME_SRC := $(shell find $(GAME_SRC_DIR) -name '*.cpp')
# OBJ := $(patsubst $(ENGINE_SRC_DIR)/%, $(OBJ_DIR)/%,$(ENGINE_SRC:.cpp=.o)) $(patsubst $(GAME_SRC_DIR)/%, $(OBJ_DIR)/%,$(GAME_SRC:.cpp=.o))
# COMPILE_OBJ = $(CC) $(CFLAGS) -c $< -o $@

# NAME = TestGame
# EXECUTABLE = $(BIN_DIR)/$(NAME)

# .PHONY: default
# default: makedir main

# makedir:
# 	mkdir -p $(BIN_DIR)
# 	mkdir -p $(OBJ_DIR)

# main: $(OBJ)
# 	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJ) $(LDLIBS)

# # Engine
# $(OBJ_DIR)/%.o: $(ENGINE_SRC_DIR)/%.cpp $(LIB)
# 	mkdir -p $(@D)
# 	$(COMPILE_OBJ)

# # Game
# $(OBJ_DIR)/%.o: $(GAME_SRC_DIR)/%.cpp $(LIB)
# 	mkdir -p $(@D)
# 	$(COMPILE_OBJ)

# .PHONY: clean
# clean:
# 	rm -rf $(OBJ_DIR)/* $(EXECUTABLE)


all:
	gcc src/Main.cpp -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=1 -o Quest.exe -lraylib -lgdi32 -lwinmm -lstdc++ -mwindows