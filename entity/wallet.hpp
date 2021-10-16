#pragma once

#include <string>

namespace my_wallets {

class Wallet {
public:
    Wallet(size_t id, const std::string& userLogin, const std::string& name,
           const std::string& description="")
    : id(id), userLogin(userLogin), name(name), description(description) {}

    size_t getId() const {
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
    size_t id;
    std::string userLogin;
    std::string name;
    std::string description;
};

} // my_wallets
