CXX = g++

# Flags
CXXFLAGS = -Wall -Wextra -O2

# Targets
all: client server

client: client1_1.cpp
	$(CXX) $(CXXFLAGS) client1_1.cpp -o client

server: server1_1.cpp
	$(CXX) $(CXXFLAGS) server1_1.cpp -o server

# Clean up
clean:
	rm -f client server