#pragma once

#include <vector>
#include <optional>

#include "data_source/user_source.hpp"
#include "entity/user.hpp"

namespace my_wallets {

class UserInMemorySource: public UserSource {
public:
    const std::vector<User>& getUsers() const override;
    virtual std::optional<User> getUser(const std::string& login) const override;
    virtual bool addUser(const std::string& login) override;
private:
    std::vector<User> users;
};

} // my_wallets
