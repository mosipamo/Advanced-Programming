CC=g++
CFLAGS=-c --std=c++11 
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

BIN_DIR =./build
EXECUTABLE = $(BIN_DIR)/main

SOURCES=$(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SOURCES))
RUN_CMD=./$(EXECUTABLE)


$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_DIR):
	mkdir $(BIN_DIR)

run: $(EXECUTABLE)
	$(RUN_CMD)

clean:
	rm -rf $(OBJS) $(EXECUTABLE) $(BIN_DIR)
	