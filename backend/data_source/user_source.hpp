#pragma once

#include <vector>
#include <optional>
#include "entity/user.hpp"

namespace my_wallets {

class UserSource {
public:
    virtual const std::vector<User> getUsers() const = 0;
    virtual std::optional<User> getUser(const std::string& login) const = 0;
    virtual bool addUser(const std::string& login) = 0;
    virtual bool removeUser(const std::string& login) = 0;
    virtual ~UserSource() {};
};

} // my_wallets
