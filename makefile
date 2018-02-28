

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


all: lib tests potlahka

lib: libpotlahka.a

tests: $(TEST_OBJECTS) libpotlahka.a
	clang++ $(TEST_LDFLAGS) -o $(TEST_OUTPUT) $(TEST_OBJECTS)
	
libpotlahka.a: $(LIB_OBJECTS)
	ar $(LIB_LDFLAGS) $
all:
	clang++ --std=c++11 -Iinc src/*.cpp -o bin/potlahka


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
ENGINE_FILES = $(wildcard engine/src/*.cpp)
ENGINE_OBJECTS = $(addprefix tmp/engine/,$(notdir $(ENGINE_FILES:.cpp=.o)))
ENGINE_CFLAGS = -std=c++11 -Iengine/inc -I3rdparty/inc -D_DEBUG
ENGINE_LDFLAGS = rcs
ENGINE_OUTPUT = lib/libaduunka.a

GAME_FILES = $(wildcard game/src/*.cpp)
GAME_OBJECTS = $(addprefix tmp/game/,$(notdir $(GAME_FILES:.cpp=.o)))
GAME_CFLAGS = -Iengine/inc -I3rdparty/inc -std=c++11 -D_DEBUG
GAME_LDFLAGS = -L/usr/local/lib -framework OpenGL -Llib -laduunka -framework Cocoa -framework IOKit -framework CoreVideo -lglew -lglfw3
GAME_OUTPUT = bin/aduunka

TEST_FILES = $(wildcard engine/test/*.cpp)
TEST_FILES += 3rdparty/src/gtest/gtest-all.cpp 3rdparty/src/gtest/gtest_main.cpp
TEST_OBJECTS = $(addprefix tmp/test/,$(notdir $(TEST_FILES:.cpp=.o)))
TEST_CFLAGS = -Iengine/inc -I3rdparty/inc -std=c++11 -D_DEBUG
TEST_LDFLAGS = -L/usr/local/lib -framework OpenGL -Llib -laduunka -framework Cocoa -framework IOKit -framework CoreVideo -lglew -lglfw3
TEST_OUTPUT = bin/libaduunka_tests

all: clean libaduunka tests aduunka 

libaduunka: dirs libaduunka.a

tests: dirs libaduunka_tests

aduunka: dirs game

clean:
	rm -rf tmp/*
	
#intermediate directories
dirs:
	mkdir -p tmp/engine tmp/test tmp/game
	
#Engine Files
libaduunka.a: $(ENGINE_OBJECTS)
	ar $(ENGINE_LDFLAGS) $(ENGINE_OUTPUT) $^
		
tmp/engine/%.o: engine/src/%.cpp
	clang++ $(ENGINE_CFLAGS) -c -o $@ $<

#Test Files

libaduunka_tests: $(TEST_OBJECTS) libaduunka.a
	clang++ $(TEST_LDFLAGS) -o $(TEST_OUTPUT) $(TEST_OBJECTS)

tmp/test/%.o: engine/test/%.cpp
	clang++ $(TEST_CFLAGS) -c -o $@ $<

tmp/test/gtest-all.o: 3rdparty/src/gtest/gtest-all.cpp
	clang++ $(TEST_CFLAGS) -c -o $@ $<

tmp/test/gtest_main.o: 3rdparty/src/gtest/gtest_main.cpp
	clang++ $(TEST_CFLAGS) -c -o $@ $<

#Games Files
game: $(GAME_OBJECTS) libaduunka.a
	clang++ $(GAME_LDFLAGS) -o $(GAME_OUTPUT) $(GAME_OBJECTS)
	
tmp/game/%.o: game/src/%.cpp
	clang++ $(GAME_CFLAGS) -c -o $@ $<