CXX = g++
CXX_FLAGS = -Wall \
			-pedantic \
			-O2 \
			-std=c++20

OBJ_FILES = $(wildcard */*.hpp)

tempenv: src/main.cpp $(OBJ_FILES) dist
	$(CXX) $(CXX_FLAGS) ./src/main.cpp -o ./dist/tempenv

#object_file_names:
#	@echo $(OBJ_FILES)

#tempenv: main $(OBJ_FILES)
#	$(CXX) $(CXX_FLAGS) ./dist/main.o $(OBJ_FILES)
#	$(CXX) $(CXX_FLAGS) ./dist/main.o -o ./dist/tempenv

#main: ./src/main.cpp dist
#	$(CXX) $(CXX_FLAGS) ./src/main.cpp -c -o ./dist/main.o

dist:
	mkdir dist
