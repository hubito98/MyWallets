#pragma once

#include <string>

class Wallet {
public:
    Wallet(int id, const std::string& userLogin, const std::string& name,
           const std::string& description="")
    : id(id), userLogin(userLogin), name(name), description(description) {}

    int getId() const {
        return id;
    }

    std::string getUserLogin() const {
        return userLogin;
    }

    std::string getName() const {
        return name;
    }

    std::string getDescription() const {
        return description;
    }

private:
    int id;
    std::string userLogin;
    std::string name;
    std::string description;
};