# ===============================
# Option Pricing Project Makefile
# ===============================

CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = option_pricing

# Automatically find source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo "Build complete!"

# Compile
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN)
	@echo "Cleaned build files."

# Run
run: $(BIN)
	./$(BIN)
