CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++20 -ggdb

# By default USA is enabled, meaning we are on an american system
COUNTRY ?= USA

ifeq ($(COUNTRY), USA)
	CXX_FLAGS += -DUSA
else
	CXX_FLAGS += -DDK
endif

BIN     := bin

# Ensure the bin directory exists
$(BIN):
	mkdir -p $(BIN)

all: $(BIN) $(BIN)/$(EXECUTABLE)
SRC     := src
INCLUDE := include
LIB     := lib
TEST	:= test
LIBRARIES   := 
EXECUTABLE  := main
TEST_EXECUTABLE := test

all: $(BIN)/$(EXECUTABLE)
# make run ARGS="person John 290700 1000"
run: clean all
	clear
	@echo "Executing..."
	./$(BIN)/$(EXECUTABLE) $(ARGS)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	@echo "Building..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $^ -o $@ $(LIBRARIES)

clean:
	@echo "Clearing..."
	-rm ./$(BIN)/*

# når du tilføjer tests: skriv $(SRC)/<implementation  af det du tester>.cpp før -o i den midterste linje nedenfor
# For at køre dansk miljø, skriv "make unit_tests COUNTRY=DK"
unit_tests: 
	@echo "Testing..."
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) $(TEST)/unit_tests/*.cpp $(SRC)/stock.cpp $(SRC)/order.cpp $(SRC)/njordx.cpp -o $(BIN)/test $(LIBRARIES)
	./$(BIN)/test