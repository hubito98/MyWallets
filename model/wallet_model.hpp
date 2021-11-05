#pragma once

#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "entity/wallet.hpp"

namespace my_wallets {
namespace model {

class WalletModel {
public:
    WalletModel(const Wallet& wallet)
    : id(wallet.getId()), name(wallet.getName()), description(wallet.getDescription()) {}

    size_t getId() const {
        return id;
    }

    friend std::ostream& operator<<(std::ostream& os, const WalletModel& walletModel) {
        os << "Wallet { id: " << walletModel.id << ", name: "<<walletModel.name<<", description: "<<walletModel.description<<" }";
        return os;
    }

    nlohmann::json toJson() const {
        nlohmann::json walletJson;
        walletJson["id"] = id;
        walletJson["name"] = name;
        walletJson["description"] = description;
        return walletJson;
    }

private:
    size_t id;
    std::string name;
    std::string description;
};

} // model
} // my_wallets