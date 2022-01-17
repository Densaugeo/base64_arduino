CXX ?= g++
CFLAGS ?= -Wall -I src

test: catch.cpp catch.hpp src/base64.hpp
	$(CXX) $(CFLAGS) catch.cpp -o catch
	./catch

upload:
	# No script - just put new version in library.properties, tag the commit, and push
	# The Arduino library registry scans GitHub every hour for new updates

clean:
	rm catch
