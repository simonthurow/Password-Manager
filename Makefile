# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Ipublic
LDFLAGS = -lcrypto -lbcrypt

# Directories
SRC_DIR = private
INC_DIR = public
OBJ_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
TARGET = pm

# Default rule
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean
clean:
	del /Q $(OBJ_DIR) $(TARGET).exe

.PHONY: all clean
