all: # block.o item.o flamingo.o
	gcc src/Main.cpp -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=1 -o Quest.exe -lraylib -lgdi32 -lwinmm -lstdc++ -mwindows

# flamingo.o: block.o item.o
# 	gcc -c flamingo.o src/Flamingo.cpp -std=c++11

# item.o:
# 	gcc -c item.o src/Item.cpp -std=c++11

# block.o:
# 	gcc -c block.o src/Block.cpp -std=c++11