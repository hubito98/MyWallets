#include "data_source/wallet_db_source.hpp"

namespace my_wallets {

const std::vector<Wallet> WalletDbSource::getWallets() const {
    std::vector<Wallet> wallets;
    auto walletsFromDb = database->getWallets();
    if (walletsFromDb != nullptr) {
        while (walletsFromDb->next()) {
            wallets.push_back(walletFromDbResult(walletsFromDb.get()));
        }
    }
    return wallets;
}

const std::vector<Wallet> WalletDbSource::getUserWallets(const std::string& userLogin) const {
    std::vector<Wallet> userWallets;
    auto walletsFromDb = database->getUserWallets(userLogin);
    if (walletsFromDb != nullptr) {
        while (walletsFromDb->next()) {
            userWallets.push_back(walletFromDbResult(walletsFromDb.get()));
        }
    }
    return userWallets;
}

std::optional<Wallet> WalletDbSource::getWallet(const size_t id) const {
    const auto walletFromDb = database->getWallet(id);
    if (walletFromDb->next()) {
        return walletFromDbResult(walletFromDb.get());
    }
    return {};
}

bool WalletDbSource::addWallet(const std::string& userLogin, const std::string& name,
                                     const std::string& description) {
    return database->addWallet(userLogin, name, description);
}

bool WalletDbSource::removeWallet(const size_t id) {
    return database->removeWallet(id);
}

} // my_wallets
