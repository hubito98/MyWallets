#pragma once

#include <string>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


namespace my_wallets {

class Database {
public:
    Database(const std::string& databaseName, const std::string& host,
             const std::string& port, const std::string& user, const std::string& password)
    : databaseName(databaseName), host(host), port(port), user(user), password(password) {
        auto session = getSession();
        session.stmt->execute("CREATE TABLE IF NOT EXISTS " + usersTable + " ( login varchar(255), PRIMARY KEY (login) )");
        session.stmt->execute("CREATE TABLE IF NOT EXISTS " + walletsTable + " ( id INT AUTO_INCREMENT, name VARCHAR(255) NOT NULL, description VARCHAR(2040), userLogin VARCHAR(255) NOT NULL, FOREIGN KEY (userLogin) REFERENCES " + usersTable + "(login) ON DELETE CASCADE, PRIMARY KEY(id) )");
        session.stmt->execute("CREATE TABLE IF NOT EXISTS " + assetsTable + " ( id INT AUTO_INCREMENT, type VARCHAR(255) NOT NULL, description VARCHAR(2040), walletId INT NOT NULL, FOREIGN KEY (walletId) REFERENCES " + walletsTable + "(id) ON DELETE CASCADE, PRIMARY KEY(id) )");
        session.stmt->execute("CREATE TABLE IF NOT EXISTS " + assetStatesTable + " ( id INT AUTO_INCREMENT, year INT NOT NULL, month INT NOT NULL, day INT NOT NULL, value DOUBLE NOT NULL, income DOUBLE NOT NULL, assetId INT NOT NULL, FOREIGN KEY (assetId) REFERENCES " + assetsTable + "(id) ON DELETE CASCADE, PRIMARY KEY(id) )");
    }

    enum class Order {DESC, ASC};

    bool addUser(const std::string& login) {
        auto session = getSession();
        try {
            session.stmt->execute("INSERT INTO " + usersTable + "(login) VALUES ('" + login + "')");
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    bool removeUser(const std::string& login) {
        auto session = getSession();
        try {
            session.stmt->execute("DELETE FROM " + usersTable + " WHERE login='" + login + "'");
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    std::unique_ptr<sql::ResultSet> getUsers() const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> users(session.stmt->executeQuery("SELECT * FROM " + usersTable));
            return users;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getUser(const std::string& login) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> user(session.stmt->executeQuery(
                    "SELECT * FROM " + usersTable + " WHERE login='" + login + "'"));
            return user;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    bool addWallet(const std::string& userLogin, const std::string& name,
                   const std::string& description="") {
        auto session = getSession();
        try {
            session.stmt->execute("INSERT INTO " + walletsTable + 
                    "(name, description, userLogin) VALUES ('" + name + "', '" + description + "', '" + userLogin + "')");
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    bool removeWallet(const size_t walletId) {
        auto session = getSession();
        try {
            session.stmt->execute("DELETE FROM " + walletsTable + " WHERE id=" + std::to_string(walletId));
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    std::unique_ptr<sql::ResultSet> getWallets() const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> wallets(session.stmt->executeQuery("SELECT * FROM " + walletsTable));
            return wallets;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getUserWallets(const std::string& userLogin) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> wallets(session.stmt->executeQuery(
                    "SELECT * FROM " + walletsTable + " WHERE userLogin='" + userLogin + "'"));
            return wallets;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }


    std::unique_ptr<sql::ResultSet> getWallet(const size_t walletId) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> wallet(session.stmt->executeQuery(
                    "SELECT * FROM " + walletsTable + " WHERE id=" + std::to_string(walletId)));
            return wallet;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    bool addAsset(const size_t walletId, const std::string& type,
                  const std::string& description=0) {
        auto session = getSession();
        try {
            session.stmt->execute("INSERT INTO " + assetsTable + 
                    "(type, description, walletId) VALUES ('" + type + "', '" + description + "', " + std::to_string(walletId) + ")");
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    bool removeAsset(const size_t assetId) {
        auto session = getSession();
        try {
            session.stmt->execute("DELETE FROM " + assetsTable + " WHERE id=" + std::to_string(assetId));
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
    }

    std::unique_ptr<sql::ResultSet> getAssets() const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> assets(session.stmt->executeQuery("SELECT * FROM " + assetsTable));
            return assets;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getWalletAssets(const size_t walletId) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> walletAssets(session.stmt->executeQuery(
                    "SELECT * FROM " + assetsTable + " WHERE walletId=" + std::to_string(walletId)));
            return walletAssets;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getAsset(const size_t assetId) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> asset(session.stmt->executeQuery(
                    "SELECT * FROM " + assetsTable + " WHERE id=" + std::to_string(assetId)));
            return asset;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    bool addAssetState(const size_t assetId, const int year, const int month, const int day,
                       const double value, const double income) {
        auto session = getSession();
        try {
            session.stmt->execute("INSERT INTO " + assetStatesTable + 
                    "(year, month, day, value, income, assetId) VALUES (" +
                    std::to_string(year) + ", " + std::to_string(month) + ", " +
                    std::to_string(day) + ", " + std::to_string(value) + ", " +
                    std::to_string(income) + ", " + std::to_string(assetId) + ")");
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
        return true;
    }

    bool removeAssetState(const size_t assetStateId) {
        auto session = getSession();
        try {
            session.stmt->execute("DELETE FROM " + assetStatesTable + " WHERE id=" + std::to_string(assetStateId));
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
            return false;
        }
        return true;
        return true;
    }

    std::unique_ptr<sql::ResultSet> getOrderedAssetStates(const Order& order) const {
        auto session = getSession();
        try {
            const auto orderString = Database::orderToString(order);
            std::unique_ptr<sql::ResultSet> assetStates(session.stmt->executeQuery("SELECT * FROM " + assetStatesTable +
                    " ORDER BY year " + orderString + ", month " + orderString + ", day " + orderString));
            return assetStates;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getParticularAssetOrderedStates(const size_t assetId, const Order& order) const {
        auto session = getSession();
        try {
            const auto orderString = Database::orderToString(order);
            std::unique_ptr<sql::ResultSet> particularAssetStates(session.stmt->executeQuery(
                    "SELECT * FROM " + assetStatesTable + " WHERE assetId=" + std::to_string(assetId) +
                    " ORDER BY year " + orderString + ", month " + orderString + ", day " + orderString));
            return particularAssetStates;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

    std::unique_ptr<sql::ResultSet> getAssetState(const size_t assetStateId) const {
        auto session = getSession();
        try {
            std::unique_ptr<sql::ResultSet> assetState(session.stmt->executeQuery(
                    "SELECT * FROM " + assetStatesTable + " WHERE id=" + std::to_string(assetStateId)));
            return assetState;
        } catch (const sql::SQLException& e) {
            std::cout<<"ERR: "<<e.what()<<";(error code: "<<e.getErrorCode()<<", SQLState: "<<e.getSQLState()<<")"<<std::endl;
        }
        return nullptr;
    }

private:
    struct MySQLSession {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        
        MySQLSession(const std::string& host, const std::string& port,
                     const std::string& user, const std::string& password,
                     const std::string& databaseName) {
            const std::string address = host + ":" + port;
            driver = get_driver_instance();
            con = driver->connect(address, user, password);
            con->setSchema(databaseName);
            stmt = con->createStatement();
        }

        ~MySQLSession() {
            if (stmt != nullptr) delete stmt;
            if (con != nullptr) delete con;
        }
    };

    MySQLSession getSession() const {
        return MySQLSession(host, port, user, password, this->databaseName);
    }

    static constexpr const char* orderToString(const Order& order) {
        if (order == Database::Order::DESC) return "DESC";
        else if (order == Database::Order::ASC) return "ASC";
        else return "";
    }

    const std::string host;
    const std::string port;
    const std::string user;
    const std::string password;

    const std::string usersTable = "Users";
    const std::string walletsTable = "Wallets";
    const std::string assetsTable = "Assets";
    const std::string assetStatesTable = "AssetStates";

    const std::string databaseName;
};

} // my_wallets