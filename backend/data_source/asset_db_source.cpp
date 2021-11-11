#include "data_source/asset_db_source.hpp"

namespace my_wallets {

const std::vector<Asset> AssetDbSource::getAssets() const {
    std::vector<Asset> assets;
    auto assetsFromDb = database->getAssets();
    if (assetsFromDb != nullptr) {
        while (assetsFromDb->next()) {
            assets.push_back(assetFromDbResults(assetsFromDb.get()));
        }
    }
    return assets;
}

const std::vector<Asset> AssetDbSource::getWalletAssets(const size_t walletId) const {
    std::vector<Asset> walletAssets;
    auto assetsFromDb = database->getWalletAssets(walletId);
    if (assetsFromDb != nullptr) {
        while (assetsFromDb->next()) {
            walletAssets.push_back(assetFromDbResults(assetsFromDb.get()));
        }
    }
    return walletAssets;
}

std::optional<Asset> AssetDbSource::getAsset(const size_t id) const {
    const auto assetFromDb = database->getAsset(id);
    if (assetFromDb->next()) {
        return assetFromDbResults(assetFromDb.get());
    }
    return {};
}

bool AssetDbSource::addAsset(const size_t walletId, const std::string& type,
                                   const std::string& description) {
    return database->addAsset(walletId, type, description);
}

bool AssetDbSource::removeAsset(const size_t id) {
    return database->removeAsset(id);
}

} // my_wallets
