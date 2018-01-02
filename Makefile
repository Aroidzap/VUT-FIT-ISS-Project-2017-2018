# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11
 
# File names
EXEC = bin/ISS2017
SOURCES = $(wildcard src/*.cpp)
OBJECTS	= $(SOURCES:src/%.cpp=obj/%.o)
SIGNAL = $(wildcard x[a-z][a-z][a-z][a-z][a-z][0-9][0-9].wav)
 
# Main target
$(EXEC): $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
obj/%.o: src/%.cpp
	mkdir -p obj
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)

# To run
run:
	$(EXEC) $(SIGNAL)