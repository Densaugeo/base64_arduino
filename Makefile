CXX ?= g++
CFLAGS ?= -Wall -I src

test: catch.cpp catch.hpp src/base64.cpp src/base64.hpp
	$(CXX) $(CFLAGS) catch.cpp src/base64.cpp -o catch
	./catch

clean:
	rm catch
