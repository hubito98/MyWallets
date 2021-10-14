#pragma once

#include <string>

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