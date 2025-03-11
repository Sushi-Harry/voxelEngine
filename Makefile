# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Libraries
LIBS := -lglfw -lGLEW -lGL -lm -ldl -lpthread

# Directories
SRC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Files
TARGET = $(BIN_DIR)/my_project
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard *.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the project
run: all
	./$(TARGET)

# Phony targets
.PHONY: all clean run
