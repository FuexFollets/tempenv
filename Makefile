LIB_ARGPARSE := ./lib/argparse/include/
LIB_TOML := ./lib/tomlplusplus/include/

CXX := g++
CXX_FLAGS := -Wall -Wextra \
			-pedantic \
			-O2 \
			-std=c++23 \
			-g \
			-I $(LIB_ARGPARSE) \
			-I $(LIB_TOML)

CPP_FILES := $(filter-out ./src/main.cpp, $(shell find ./src -name "*.cpp"))
MAIN_FILE := $(shell find ./src -name "main.cpp")
HEADER_FILES := $(shell find ./src -name "*.hpp") $(shell find ./src -name "*.h")
SOURCE_FILES := $(HEADER_FILES) $(CPP_FILES)
OBJECT_FILES := $(patsubst ./src/%.cpp, ./dist/objects/%.o, $(CPP_FILES))

# For running tests
COMPILE_OBJECT_FILES ?= "TRUE"
NAME ?=

clean:
	rm -r ./dist

tempenv: $(OBJECT_FILES) dist_dir
	$(CXX) $(CXX_FLAGS) $(MAIN_FILE) -c -o ./dist/objects/main.o
	$(CXX) $(CXX_FLAGS) $(OBJECT_FILES) ./dist/objects/main.o -o ./dist/tempenv

runtest: test_$(NAME) dist_dir
	./dist/$<

test_%: ./dist/objects/test_%.o $(OBJECT_FILES) dist_dir # Makes test binaries
	ifeq ($(COMPILE_OBJECT_FILES), "TRUE")
		$(CXX) $(CXX_FLAGS) $(OBJECT_FILES) $< -o ./dist/$@
	endif

	ifeq ($(COMPILE_OBJECT_FILES), "FALSE")
		$(CXX) $(CXX_FLAGS) $< -o ./dist/$@
	endif

	@echo
	./dist/$@


./dist/objects/test_%.o: ./tests/test_%.cpp dist_dir
	$(CXX) $(CXX_FLAGS) -c $< -o $@

./dist/objects/%.o: ./src/%.cpp $(HEADER_FILES) dist_dir # Makes object files
	ifeq ($(COMPILE_OBJECT_FILES), "TRUE")
		$(CXX) $(CXX_FLAGS) -c $< -o $@
	endif

dist_dir:
	@mkdir -p ./dist/objects
	@mkdir -p ./dist/tests

print: # Tests for wildcards
	@echo $(CPP_FILES)
	@echo $(MAIN_FILE)
	@echo $(OBJECT_FILES)
	@echo $(SOURCE_FILES)
	@echo $(NAME)
