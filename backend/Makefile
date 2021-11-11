PROG = main
CC = g++
# CPPFLAGS = -I. -I/usr/local/mysql-connector-c++/include/ -L/usr/local/mysql-connector-c++/lib64 -lmysqlcppconn8 -std=c++17 -pthread -lboost_system -lserved
CPPFLAGS = -I. -I/usr/include/ -L/usr/lib/aarch64-linux-gnu -lmysqlcppconn -std=c++17 -pthread -lboost_system -lserved
# g++ test.cpp -std=c++17 -I/usr/include/ -L/usr/lib/aarch64-linux-gnu -lmysqlcppconn

compile: main.cpp frontend/my_wallets.cpp data_source/user_db_source.cpp data_source/wallet_db_source.cpp \
		data_source/asset_db_source.cpp data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp \
		model/basic_wallet_statistics_model.cpp
	$(CC) -o $(PROG) main.cpp frontend/my_wallets.cpp data_source/user_db_source.cpp data_source/wallet_db_source.cpp \
		data_source/asset_db_source.cpp data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp \
		model/basic_wallet_statistics_model.cpp $(CPPFLAGS)

run: compile
	DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

run_rest: compile
	EXECUTE_TYPE=rest DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

run_production: compile
	DB_NAME=my_wallets_db MY_ENV=hello DYLD_LIBRARY_PATH=/usr/local/mysql-connector-c++/lib64/ ./$(PROG)

clean:
	rm -rf core $(PROG)