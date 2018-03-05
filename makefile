

LIB_FILES = src/image.cpp src/random.cpp src/vec3.cpp
LIB_OBJECTS = $(addprefix tmp/lib/,$(notdir $(LIB_FILES:.cpp=.o)))
LIB_CFLAGS = -Iinc --std=c++11
LIB_LDFLAGS = rcs
LIB_OUTPUT = lib/libpotlahka.a

MAIN_FILES = src/main.cpp
MAIN_OBJECTS = $(addprefix tmp/main/,$(notdir $(MAIN_FILES:.cpp=.o)))
MAIN_CFLAGS = -Iinc --std=c++11
MAIN_LDFLAGS = -Llib -lpotlotlahka
MAIN_OUTPUT = bin/potlahka


TEST_FILES = $(wildcard test/*.cpp) 
TEST_OBJECTS = $(addprefix tmp/tests/,$(notdir $(TEST_FILES:.cpp=.o)))
TEST_CFLAGS = -Iinc --std=c++11
TEST_LDFLAGS = -Llib -lpotlotlahka
TEST_OUTPUT = bin/potlahka_tests

all:
	clang++ -O2 --std=c++11 -Iinc src/*.cpp -o bin/potlahka


	
	
