#include "data_source/wallet_db_source.hpp"

namespace my_wallets {

const std::vector<Wallet> WalletDbSource::getWallets() const {
    std::vector<Wallet> wallets;
    auto walletsFromDb = database->getWallets();
    std::transform(walletsFromDb.begin(), walletsFromDb.end(), std::back_inserter(wallets), WalletDbSource::walletFromDbResult);
    return wallets;
}

const std::vector<Wallet> WalletDbSource::getUserWallets(const std::string& userLogin) const {
    std::vector<Wallet> userWallets;
    auto walletsFromDb = database->getUserWallets(userLogin);
    std::transform(walletsFromDb.begin(), walletsFromDb.end(), std::back_inserter(userWallets), WalletDbSource::walletFromDbResult);
    return userWallets;
}

std::optional<Wallet> WalletDbSource::getWallet(const size_t id) const {
    const auto walletFromDb = database->getWallet(id);
    if (walletFromDb.isNull()) return {};
    return this->walletFromDbResult(walletFromDb);
}

bool WalletDbSource::addWallet(const std::string& userLogin, const std::string& name,
                                     const std::string& description) {
    return database->addWallet(userLogin, name, description);
}

bool WalletDbSource::removeWallet(const size_t id) {
    return database->removeWallet(id);
}

} // my_wallets
