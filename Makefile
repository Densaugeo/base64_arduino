CXX ?= g++
CFLAGS ?= -Wall

test: catch.cpp catch.hpp base64.c base64.h
	$(CXX) $(CFLAGS) catch.cpp base64.c -o catch
	./catch

clean:
	rm catch
