#pragma once

#include <vector>
#include <optional>

#include "dataSource/walletSource.hpp"
#include "entity/wallet.hpp"

class WalletInMemorySource: public WalletSource {
public:
    WalletInMemorySource();
    const std::vector<Wallet>& getWallets() const override;
    const std::vector<Wallet> getUserWallets(const std::string& userLogin) const override;
    std::optional<Wallet> getWallet(const int id) const override;
    bool addWallet(const std::string& userLogin, const std::string& name,
                   const std::string& description="") override;
private:
    std::vector<Wallet> wallets;
};
