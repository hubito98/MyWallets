#pragma once

#include <vector>
#include <optional>
#include "entity/wallet.hpp"

namespace my_wallets {

class WalletSource {
public:
    virtual const std::vector<Wallet> getWallets() const = 0;
    virtual const std::vector<Wallet> getUserWallets(const std::string& userLogin) const = 0;
    virtual std::optional<Wallet> getWallet(const size_t id) const = 0;
    virtual bool addWallet(const std::string& userLogin, const std::string& name,
                           const std::string& description="") = 0;
    virtual ~WalletSource() {};
};

} // my_wallets
