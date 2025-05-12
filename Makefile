# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Source and output
SRC = *.cpp
TARGET = match

# Default target to compile the program
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean: remove the compiled executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: clean
