#pragma once

#include <vector>
#include <optional>

#include <mysqlx/xdevapi.h>

#include "data_source/user_source.hpp"
#include "entity/user.hpp"
#include "data_source/database.hpp"

namespace my_wallets {

class UserDbSource: public UserSource {
public:
    UserDbSource(std::shared_ptr<Database> database)
    : database(database) {};
    const std::vector<User> getUsers() const override;
    virtual std::optional<User> getUser(const std::string& login) const override;
    virtual bool addUser(const std::string& login) override;
private:
    static User userFromDbResult(const mysqlx::Row& userFromDb) {
        return User((std::string)userFromDb[0]);
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
