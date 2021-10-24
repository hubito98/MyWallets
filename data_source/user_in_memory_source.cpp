#include "data_source/user_in_memory_source.hpp"

namespace my_wallets {

const std::vector<User> UserInMemorySource::getUsers() const {
    return users;
}

std::optional<User> UserInMemorySource::getUser(const std::string& login) const {
    auto foundUser = std::find_if(users.begin(), users.end(), [&login](const User& user) {
        return user.getLogin() == login;
    });
    if (foundUser == users.end()) return {};
    return *foundUser;
}

bool UserInMemorySource::addUser(const std::string& login) {
    if (std::none_of(users.begin(), users.end(), [&login](const User& user) {return user.getLogin() == login;})) {
        users.push_back(User(login));
        return true;
    } else {
        return false;
    }
}

} // my_wallets
