CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = hello
SRC = main.cpp
HEADERS = CRTP.h

# Add $(HEADERS) as a prerequisite to the target
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean