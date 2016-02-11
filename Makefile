CXX ?= g++
CFLAGS ?= -Wall

test: catch.cpp catch.hpp base64.cpp base64.hpp
	$(CXX) $(CFLAGS) catch.cpp base64.cpp -o catch
	./catch

clean:
	rm catch
