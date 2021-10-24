#include "data_source/wallet_in_memory_source.hpp"

namespace my_wallets {

const std::vector<Wallet> WalletInMemorySource::getWallets() const {
    return wallets;
}

const std::vector<Wallet> WalletInMemorySource::getUserWallets(const std::string& userLogin) const {
    std::vector<Wallet> userWallets;
    std::copy_if(wallets.begin(), wallets.end(), std::back_inserter(userWallets), [&userLogin](const Wallet& wallet){
        return wallet.getUserLogin() == userLogin;
    });
    return userWallets;
}

std::optional<Wallet> WalletInMemorySource::getWallet(const size_t id) const {
    auto foundWallet = std::find_if(wallets.begin(), wallets.end(), [id](const Wallet& wallet){
        return wallet.getId() == id;
    });
    if (foundWallet == wallets.end()) return {};
    return *foundWallet;
}

bool WalletInMemorySource::addWallet(const std::string& userLogin, const std::string& name,
                                     const std::string& description) {
    wallets.push_back(Wallet(wallets.size(), userLogin, name, description));
    return true;
}

} // my_wallets
