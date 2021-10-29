PROG = main
CC = g++
CPPFLAGS = -I. -I/usr/local/mysql-connector-c++/include/ -L/usr/local/mysql-connector-c++/lib64 -lmysqlcppconn8 -std=c++17

compile: main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp frontend/my_wallets.cpp \
		data_source/user_db_source.cpp data_source/wallet_db_source.cpp data_source/asset_db_source.cpp \
		data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp
	$(CC) -o $(PROG) main.cpp data_source/user_in_memory_source.cpp data_source/asset_state_in_memory_source.cpp \
		data_source/wallet_in_memory_source.cpp data_source/asset_in_memory_source.cpp frontend/my_wallets.cpp \
		data_source/user_db_source.cpp data_source/wallet_db_source.cpp data_source/asset_db_source.cpp \
		data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp $(CPPFLAGS)

run: compile
	MY_ENV=hello DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

run_production: compile
	DB_NAME=my_wallets_db MY_ENV=hello DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

clean:
	rm -rf core $(PROG)