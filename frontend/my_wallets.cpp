#include "my_wallets.hpp"

namespace my_wallets {
namespace frontend {

const std::vector<UserModel> MyWallets::getUsers() const {
    std::vector<UserModel> users;
    const auto usersFromSource = userSource->getUsers();
    std::transform(usersFromSource.begin(), usersFromSource.end(), std::back_inserter(users),
                   [](const auto& user){
        return UserModel(user);
    });
    return users;
}

bool MyWallets::addUser(const std::string& login) {
    return userSource->addUser(login);
}

const std::vector<WalletModel> MyWallets::getUserWallets(const UserModel& userModel) const {
    const auto userWalletsData = walletSource->getUserWallets(userModel.getLogin());
    std::vector<WalletModel> userWallets;
    std::transform(userWalletsData.begin(), userWalletsData.end(), std::back_inserter(userWallets),
                   [](const auto& wallet) {
        return WalletModel(wallet);
    });
    return userWallets;
}

bool MyWallets::addWallet(const std::string& userLogin, const std::string& name,
                          const std::string& description) {
    return walletSource->addWallet(userLogin, name, description);
}

const std::vector<AssetModel> MyWallets::getAssetsFromWallet(const WalletModel& walletModel) const {
    const auto walletAssetsData = assetSource->getWalletAssets(walletModel.getId());
    std::vector<AssetModel> walletAssets;
    std::transform(walletAssetsData.begin(), walletAssetsData.end(), std::back_inserter(walletAssets),
                   [](const auto& asset){
        return AssetModel(asset);
    });
    return walletAssets;
}

bool MyWallets::addAsset(const size_t walletId, const std::string& type,
                         const std::string& description) {
    return assetSource->addAsset(walletId, type, description);
}

const std::vector<AssetStateModel> MyWallets::getAssetStatesOfAsset(const AssetModel& assetModel) const {
    const auto assetStateOfAssetData = assetStateSource->getParticularAssetStates(assetModel.getId());
    std::vector<AssetStateModel> assetStatesOfAsset;
    std::transform(assetStateOfAssetData.begin(), assetStateOfAssetData.end(), std::back_inserter(assetStatesOfAsset),
                   [](const auto& assetState){
        return AssetStateModel(assetState);
    });
    return assetStatesOfAsset;
}

bool MyWallets::addAssetState(const size_t assetId, const Date& date, const double value,
                              const double income) {
    return assetStateSource->addAssetState(assetId, date, value, income);
}

} // frontend
} // my_wallets