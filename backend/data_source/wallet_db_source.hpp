#pragma once

#include <vector>
#include <optional>

#include <cppconn/resultset.h>

#include "data_source/wallet_source.hpp"
#include "data_source/database.hpp"
#include "entity/wallet.hpp"

namespace my_wallets {

class WalletDbSource: public WalletSource {
public:
    WalletDbSource(std::shared_ptr<Database> database)
    : database(database) {}
    const std::vector<Wallet> getWallets() const override;
    const std::vector<Wallet> getUserWallets(const std::string& userLogin) const override;
    std::optional<Wallet> getWallet(const size_t id) const override;
    bool addWallet(const std::string& userLogin, const std::string& name,
                   const std::string& description="") override;
    bool removeWallet(const size_t id) override;
private:
    static Wallet walletFromDbResult(const sql::ResultSet* walletFromDb) {
        return Wallet(walletFromDb->getInt(1), walletFromDb->getString(4),
                      walletFromDb->getString(2), walletFromDb->getString(3));
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
