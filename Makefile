LIB_ARGPARSE := ./lib/argparse/include/
LIB_TOML := ./lib/tomlplusplus/include/

CXX := g++
CXX_FLAGS := -Wall \
			-pedantic \
			-pipe \
			-g \
			-std=c++23 \
			-I $(LIB_ARGPARSE) \
			-I $(LIB_TOML)
LDFLAGS :=

PROGRAM_NAME := tempenv
CPP_FILES := $(filter-out ./src/main.cpp, $(shell find ./src -name "*.cpp"))
MAIN_FILE := $(shell find ./src -name "main.cpp")
HEADER_FILES := $(shell find ./src -name "*.hpp") $(shell find ./src -name "*.h")
SOURCE_FILES := $(HEADER_FILES) $(CPP_FILES)
OBJECT_FILES := $(patsubst ./src/%.cpp, ./dist/objects/%.o, $(CPP_FILES))

# For running tests
TESTNAME ?=

clean:
	rm -fr ./dist/*

$(PROGRAM_NAME): $(OBJECT_FILES) ./dist/objects/main.o | dist_dir
	# $(CXX) $(CXX_FLAGS) $(MAIN_FILE) -c -o ./dist/objects/main.o
	$(CXX) $(CXX_FLAGS) $(OBJECT_FILES) ./dist/objects/main.o -o ./dist/$(PROGRAM_NAME)

runtest: test_$(TESTNAME) | dist_dir
	./dist/$<

test_%: ./dist/tests/test_%.o $(OBJECT_FILES) | dist_dir # Makes test binaries
	$(CXX) $(CXX_FLAGS) $(OBJECT_FILES) -g $< -o ./dist/$@

	@echo
	./dist/$@


./dist/tests/test_%.o: ./tests/test_%.cpp | dist_dir
	$(CXX) $(CXX_FLAGS) -g -c $< -o $@

./dist/objects/%.o: ./src/%.cpp $(HEADER_FILES) | dist_dir # Makes object files
	$(CXX) $(CXX_FLAGS) -c $< -o $@

dist_dir:
	@-mkdir -p ./dist/objects
	@-mkdir -p ./dist/tests

print: # Tests for wildcards
	@echo "PROGRAM_NAME: $(PROGRAM_NAME)"
	@echo "CPP_FILES: $(CPP_FILES)"
	@echo "MAIN_FILE: $(MAIN_FILE)"
	@echo "OBJECT_FILES: $(OBJECT_FILES)"
	@echo "SOURCE_FILES: $(SOURCE_FILES)"
	@echo "TESTNAME: $(TESTNAME)"
