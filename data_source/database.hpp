#pragma once

#include <string>
#include <iostream>

#include <mysqlx/xdevapi.h>

namespace my_wallets {

class Database {
public:
    Database(const std::string& databaseName)
    : databaseName(databaseName) {
        auto session = getSession();
        session.sql("CREATE DATABASE IF NOT EXISTS " + databaseName).execute();
        session.sql("USE " + databaseName).execute();
        session.sql("CREATE TABLE IF NOT EXISTS " + usersTable + " ( login varchar(255), PRIMARY KEY (login) )").execute();
        session.sql("CREATE TABLE IF NOT EXISTS " + walletsTable + " ( id INT AUTO_INCREMENT, name VARCHAR(255) NOT NULL, description VARCHAR(2040), userLogin VARCHAR(255) NOT NULL, FOREIGN KEY (userLogin) REFERENCES " + usersTable + "(login) ON DELETE CASCADE, PRIMARY KEY(id) )").execute();
        session.sql("CREATE TABLE IF NOT EXISTS " + assetsTable + " ( id INT AUTO_INCREMENT, type VARCHAR(255) NOT NULL, description VARCHAR(2040), walletId INT NOT NULL, FOREIGN KEY (walletId) REFERENCES " + walletsTable + "(id) ON DELETE CASCADE, PRIMARY KEY(id) )").execute();
        session.sql("CREATE TABLE IF NOT EXISTS " + assetStatesTable + " ( id INT AUTO_INCREMENT, year INT NOT NULL, month INT NOT NULL, day INT NOT NULL, value DOUBLE NOT NULL, income DOUBLE NOT NULL, assetId INT NOT NULL, FOREIGN KEY (assetId) REFERENCES " + assetsTable + "(id) ON DELETE CASCADE, PRIMARY KEY(id) )").execute();
        session.close();
    }

    bool addUser(const std::string& login) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(usersTable);
        try {
            table.insert("login").values(login).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while adding user with login: "<<login<<std::endl;
            return false;
        }
        return true;
    }

    bool removeUser(const std::string& login) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(usersTable);
        try {
            table.remove().where("login = :login").bind("login", login).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while removing user with login: "<<login<<std::endl;
            return false;
        }
        return true;
    }

    mysqlx::RowResult getUsers() const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(usersTable);
        auto results = table.select("*").execute();
        return results;
    }

    mysqlx::Row getUser(const std::string& login) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(usersTable);
        auto results = table.select("*").where("login = :login").bind("login", login).execute();
        return results.fetchOne();
    }

    bool addWallet(const std::string& userLogin, const std::string& name,
                   const std::string& description="") {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(walletsTable);
        try {
            table.insert("name", "description", "userLogin").values(name, description, userLogin).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while adding Wallet for user: "<<userLogin<<std::endl;
            return false;
        }
        return true;
    }

    bool removeWallet(const size_t walletId) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(walletsTable);
        try {
            table.remove().where("id = :walletId").bind("walletId", walletId).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while removing wallet with id: "<<walletId<<std::endl;
            return false;
        }
        return true;
    }

    mysqlx::RowResult getWallets() const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(walletsTable);
        auto results = table.select("*").execute();
        return results;
    }

    mysqlx::RowResult getUserWallets(const std::string& userLogin) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(walletsTable);
        auto results = table.select("*").where("userLogin = :userLogin").bind("userLogin", userLogin).execute();
        return results;
    }


    mysqlx::Row getWallet(const size_t walletId) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(walletsTable);
        auto results = table.select("*").where("id = :id").bind("id", walletId).execute();
        return results.fetchOne();
    }

    bool addAsset(const size_t walletId, const std::string& type,
                  const std::string& description=0) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetsTable);
        try {
            table.insert("type", "description", "walletId").values(type, description, walletId).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while adding Asset for wallet: "<<walletId<<std::endl;
            return false;
        }
        return true;
    }

    bool removeAsset(const size_t assetId) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetsTable);
        try {
            table.remove().where("id = :assetId").bind("assetId", assetId).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while removing asset with id: "<<assetId<<std::endl;
            return false;
        }
        return true;
    }

    mysqlx::RowResult getAssets() const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetsTable);
        auto results = table.select("*").execute();
        return results;
    }

    mysqlx::RowResult getWalletAssets(const size_t walletId) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetsTable);
        auto results = table.select("*").where("walletId = :walletId").bind("walletId", walletId).execute();
        return results;
    }

    mysqlx::Row getAsset(const size_t assetId) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetsTable);
        auto results = table.select("*").where("id = :id").bind("id", assetId).execute();
        return results.fetchOne();
    }

    bool addAssetState(const size_t assetId, const int year, const int month, const int day,
                       const double value, const double income) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetStatesTable);
        try {
            table.insert("year", "month", "day", "value", "income", "assetId")
                    .values(year, month, day, value, income, assetId).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while adding AssetState for asset: "<<assetId<<std::endl;
            return false;
        }
        return true;
    }

    bool removeAssetState(const size_t assetStateId) {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetStatesTable);
        try {
            table.remove().where("id = :assetStateId").bind("assetStateId", assetStateId).execute();
        } catch (const mysqlx::abi2::Error& error) {
            std::cout<<"Error while removing asset state with id: "<<assetStateId<<std::endl;
            return false;
        }
        return true;
    }

    mysqlx::RowResult getAssetStates() const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetStatesTable);
        auto results = table.select("*").orderBy("year", "month", "day").execute();
        return results;
    }

    mysqlx::RowResult getParticularAssetStates(const size_t assetId) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetStatesTable);
        auto results = table.select("*").where("assetId = :assetId").orderBy("year DESC", "month DESC", "day DESC")
                .bind("assetId", assetId).execute();
        return results;
    }

    mysqlx::Row getAssetState(const size_t assetStateId) const {
        auto session = getSession();
        auto schema = session.getSchema(databaseName);
        auto table = schema.getTable(assetStatesTable);
        auto results = table.select("*").where("id = :id").bind("id", assetStateId).execute();
        return results.fetchOne();
    }

private:
    mysqlx::Session getSession() const {
        return mysqlx::Session(host, port, user, password);
    }

    const std::string host = "localhost";
    const size_t port = 33060;
    const std::string user = "root";
    const std::string password = "password";

    const std::string usersTable = "Users";
    const std::string walletsTable = "Wallets";
    const std::string assetsTable = "Assets";
    const std::string assetStatesTable = "AssetStates";

    const std::string databaseName;
};

} // my_wallets