#include "data_source/user_db_source.hpp"

namespace my_wallets {

const std::vector<User> UserDbSource::getUsers() const {
    std::vector<User> users;
    auto usersFromDb = database->getUsers();
    std::transform(usersFromDb.begin(), usersFromDb.end(), std::back_inserter(users), UserDbSource::userFromDbResult);
    return users;
}

std::optional<User> UserDbSource::getUser(const std::string& login) const {
    const auto userFromDb = database->getUser(login);
    if (userFromDb.isNull()) return {};
    return UserDbSource::userFromDbResult(userFromDb);
}

bool UserDbSource::addUser(const std::string& login) {
    return database->addUser(login);
}

} // my_wallets
