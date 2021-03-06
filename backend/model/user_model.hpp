#pragma once

#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "entity/user.hpp"

namespace my_wallets {
namespace model {

class UserModel {
public:
    UserModel(const User& user)
    : login(user.getLogin()) {}

    std::string getLogin() const {
        return login;
    }

    friend std::ostream& operator<<(std::ostream& os, const UserModel& userModel) {
        os << "User { login: " << userModel.login << " }";
        return os;
    }

    nlohmann::json toJson() const {
        nlohmann::json userJson;
        userJson["login"] = login;
        return userJson;
    }

private:
    std::string login;
};

} // model
} // my_wallets