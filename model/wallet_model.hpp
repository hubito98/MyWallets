#pragma once

#include <string>
#include <iostream>

#include "entity/wallet.hpp"

namespace my_wallets {

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
private:
    size_t id;
    std::string name;
    std::string description;
};

}