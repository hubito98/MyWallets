PROG = main
CC = g++
CPPFLAGS = -I. -I/usr/local/mysql-connector-c++/include/ -L/usr/local/mysql-connector-c++/lib64 -lmysqlcppconn8 -std=c++17

compile: main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp my_wallets.cpp \
		data_source/user_db_source.cpp data_source/wallet_db_source.cpp
	$(CC) -o $(PROG) main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp my_wallets.cpp \
		data_source/user_db_source.cpp data_source/wallet_db_source.cpp $(CPPFLAGS)

run: compile
	MY_ENV=hello DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

clean:
	rm -rf core $(PROG)