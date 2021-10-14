#pragma once

#include <vector>
#include <optional>
#include "entity/user.hpp"

class UserSource {
public:
    virtual const std::vector<User>& getUsers() const = 0;
    virtual std::optional<User> getUser(const std::string& login) const = 0;
    virtual bool addUser(const std::string& login) = 0;
};