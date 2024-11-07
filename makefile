CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++20 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib
TEST	:= test
LIBRARIES   := 
EXECUTABLE  := main
TEST_EXECUTABLE := test


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "Building..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o $@ $(LIBRARIES)

clean:
	@echo "Clearing..."
	-rm $(BIN)/*

unit_tests:
	@echo "Testing..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $(TEST)/unit_tests/*.cpp -o $(BIN)/test $(LIBRARIES)
	./$(BIN)/test