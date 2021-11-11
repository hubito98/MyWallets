#pragma once

#include <vector>
#include <optional>

#include <cppconn/resultset.h>

#include "data_source/user_source.hpp"
#include "entity/user.hpp"
#include "data_source/database.hpp"

namespace my_wallets {

class UserDbSource: public UserSource {
public:
    UserDbSource(std::shared_ptr<Database> database)
    : database(database) {};
    const std::vector<User> getUsers() const override;
    std::optional<User> getUser(const std::string& login) const override;
    bool addUser(const std::string& login) override;
    bool removeUser(const std::string& login) override;
private:
    static User userFromDbResult(const sql::ResultSet* userFromDb) {
        return User(userFromDb->getString(1));
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
