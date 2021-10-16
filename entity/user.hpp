#pragma once

#include <string>

namespace my_wallets {

class User {
public:
    User(const std::string& login)
    : login(login) {}

    std::string getLogin() const {
        return login;
    }
private:
    std::string login;
};

} // my_wallets
