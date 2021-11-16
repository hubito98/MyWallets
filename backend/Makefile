PROG = main
CC = g++
CPPFLAGS = -O3 -I. -I/usr/include/ -L/usr/lib/aarch64-linux-gnu -lmysqlcppconn -std=c++17 -pthread -lboost_system -lserved

compile: main.cpp frontend/my_wallets.cpp data_source/user_db_source.cpp data_source/wallet_db_source.cpp \
		data_source/asset_db_source.cpp data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp \
		model/basic_wallet_statistics_model.cpp
	$(CC) -o $(PROG) main.cpp frontend/my_wallets.cpp data_source/user_db_source.cpp data_source/wallet_db_source.cpp \
		data_source/asset_db_source.cpp data_source/asset_state_db_source.cpp model/basic_asset_statistics_model.cpp \
		model/basic_wallet_statistics_model.cpp $(CPPFLAGS)

clean:
	rm -rf core $(PROG)