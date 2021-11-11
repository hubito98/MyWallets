#include "data_source/user_db_source.hpp"

namespace my_wallets {

const std::vector<User> UserDbSource::getUsers() const {
    std::vector<User> users;
    auto usersFromDb = database->getUsers();
    if (usersFromDb != nullptr) {
        while (usersFromDb->next()) {
            users.push_back(userFromDbResult(usersFromDb.get()));
        }
    }
    return users;
}

std::optional<User> UserDbSource::getUser(const std::string& login) const {
    const auto userFromDb = database->getUser(login);
    if (userFromDb->next()) {
        return userFromDbResult(userFromDb.get());
    }
    return {};
}

bool UserDbSource::addUser(const std::string& login) {
    return database->addUser(login);
}

bool UserDbSource::removeUser(const std::string& login) {
    return database->removeUser(login);
}

} // my_wallets
