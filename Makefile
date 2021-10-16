PROG = main
CC = g++
CPPFLAGS = -I. -std=c++17

compile: main.cpp dataSource/userInMemorySource.cpp dataSource/assetStateInMemorySource.cpp \
		dataSource/walletInMemorySource.cpp dataSource/assetInMemorySource.cpp
	$(CC) -o $(PROG) main.cpp dataSource/userInMemorySource.cpp dataSource/assetStateInMemorySource.cpp \
			dataSource/walletInMemorySource.cpp dataSource/assetInMemorySource.cpp $(CPPFLAGS)

run: compile
	./$(PROG)

clean:
	rm -rf core $(PROG)