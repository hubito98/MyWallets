PROG = main
CC = g++
CPPFLAGS = -I. -std=c++17

compile: main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp my_wallets.cpp
	$(CC) -o $(PROG) main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp my_wallets.cpp $(CPPFLAGS)

run: compile
	./$(PROG)

clean:
	rm -rf core $(PROG)