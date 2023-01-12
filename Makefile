LIB_ARGPARSE = ./lib/argparse/include/
LIB_JSON = ./lib/json/include/

CXX = g++
CXX_FLAGS = -Wall \
			-pedantic \
			-O2 \
			-std=c++20 \
			-g \
			-I $(LIB_ARGPARSE) \
			-I $(LIB_JSON)

CPP_SRC_FILES = $(wildcard */*.cpp)
CPP_OBJECT_FILES = $(patsubst src/%.cpp, dist/%.o, $(CPP_SRC_FILES))

tempenv: $(CPP_OBJECT_FILES) dist_dir
	$(CXX) $(CXX_FLAGS) ./dist/*.o -o ./dist/tempenv

./dist/%.o: ./src/%.cpp dist_dir
	$(CXX) $(CXX_FLAGS) -c $< -o $@

dist_dir:
	@mkdir -p ./dist/

list_src_dist:
	@echo $(CPP_SRC_FILES)
	@echo $(CPP_OBJECT_FILES)
	
