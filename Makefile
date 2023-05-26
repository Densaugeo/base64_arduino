CXX ?= g++
CFLAGS ?= -Wall -I src
SOURCES = $(wildcard src/*.cpp)

test: catch-standard.cpp catch-base64-url.cpp catch.hpp src/base64.hpp $(SOURCES)
	$(CXX) $(CFLAGS) catch-standard.cpp $(SOURCES) -o catch
	./catch
	$(CXX) $(CFLAGS) catch-base64-url.cpp $(SOURCES) -o catch
	./catch

upload:
	# No script - just put new version in library.properties, tag the commit, and push
	# The Arduino library registry scans GitHub every hour for new updates

clean:
	rm catch
