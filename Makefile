CXX ?= g++
CFLAGS ?= -Wall -I src

test: catch-standard.cpp catch-base64-url.cpp catch.hpp src/base64.hpp
	$(CXX) $(CFLAGS) catch-standard.cpp -o catch
	./catch
	$(CXX) $(CFLAGS) catch-base64-url.cpp -o catch
	./catch

upload:
	# No script - just put new version in library.properties, tag the commit, and push
	# The Arduino library registry scans GitHub every hour for new updates

clean:
	rm catch
