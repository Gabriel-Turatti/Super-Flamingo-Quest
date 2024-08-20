# CPP = gcc
# OB = objects
# S = src
# HD = header

# rayzinho = -I/include/raylib.h
# FLAGS =  -std=c++11

# all: $(OB)/play.o
# 	$(CPP) src/Main.cpp -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=1 -o Quest.exe -lraylib -lgdi32 -lwinmm -lstdc++ -mwindows

# $(OB)/play.o: $(OB)/flamingo.o $(OB)/maploader.o
# 	$(CPP) -c src/Play.cpp -std=c++11

# $(OB)/maploader.o:
# 	$(CPP) -c src/maploader.cpp -std=c++11




CPP = g++
OB = objects
S = src
HD = include

# Include path for raylib
INCLUDES = -I/include/raylib.h
# Library path for raylib
LDFLAGS = -L/lib/libraylib.a -lraylib -lgdi32 -lwinmm -lstdc++ -mwindows

FLAGS = -std=c++17 -D_GLIBCXX_USE_CXX11_ABI=1

OBJS = $(OB)/Block.o $(OB)/Flamingo.o $(OB)/Functions.o $(OB)/Effect.o $(OB)/Item.o $(OB)/Enemy.o $(OB)/MapLoader.o $(OB)/Play.o $(OB)/Main.o $(OB)/ItemHandler.o $(OB)/BlockHandler.o

# Ensure the object directory exists
$(OBJS): | $(OB)

# Target to create the object directory
$(OB):
	mkdir -p $(OB)

# Target to build the final executable
all: $(OBJS)
	$(CPP) -o Quest.exe $(OBJS) $(FLAGS) $(LDFLAGS)

# Rules to compile each .cpp file into .o file
$(OB)/Block.o: $(S)/Block.cpp $(HD)/Block.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Block.cpp -o $@

$(OB)/Flamingo.o: $(S)/Flamingo.cpp $(HD)/Flamingo.hpp $(HD)/Block.hpp $(HD)/Effect.hpp $(HD)/Play.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Flamingo.cpp -o $@

$(OB)/Effect.o: $(S)/Effect.cpp $(HD)/Effect.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Effect.cpp -o $@

$(OB)/Item.o: $(S)/Item.cpp $(HD)/Item.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Item.cpp -o $@

$(OB)/Enemy.o: $(S)/Enemy.cpp $(HD)/Enemy.hpp $(HD)/Block.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Enemy.cpp -o $@

$(OB)/Functions.o: $(S)/Functions.cpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Functions.cpp -o $@

$(OB)/MapLoader.o: $(S)/MapLoader.cpp $(HD)/MapLoader.hpp $(HD)/Item.hpp $(HD)/Enemy.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/MapLoader.cpp -o $@

$(OB)/Play.o: $(S)/Play.cpp $(HD)/Play.hpp $(HD)/Flamingo.hpp $(HD)/MapLoader.hpp $(HD)/Enemy.hpp $(HD)/Effect.hpp $(HD)/ItemHandler.hpp $(HD)/BlockHandler.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Play.cpp -o $@

$(OB)/Main.o: $(S)/Main.cpp $(HD)/Play.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/Main.cpp -o $@

$(OB)/ItemHandler.o: $(S)/ItemHandler.cpp $(HD)/ItemHandler.hpp $(HD)/Item.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/ItemHandler.cpp -o $@

$(OB)/BlockHandler.o: $(S)/BlockHandler.cpp $(HD)/BlockHandler.hpp $(HD)/Block.hpp
	$(CPP) $(FLAGS) $(INCLUDES) -c $(S)/BlockHandler.cpp -o $@

# Clean up
.PHONY: clean
clean:
	rm -rf $(OB) Quest.exe