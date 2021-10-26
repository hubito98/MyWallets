#include "data_source/asset_db_source.hpp"

namespace my_wallets {

const std::vector<Asset> AssetDbSource::getAssets() const {
    std::vector<Asset> assets;
    auto assetsFromDb = database->getAssets();
    std::transform(assetsFromDb.begin(), assetsFromDb.end(), std::back_inserter(assets), AssetDbSource::assetFromDbResults);
    return assets;
}

const std::vector<Asset> AssetDbSource::getWalletAssets(const size_t walletId) const {
    std::vector<Asset> walletAssets;
    auto assetsFromDb = database->getWalletAssets(walletId);
    std::transform(assetsFromDb.begin(), assetsFromDb.end(), std::back_inserter(walletAssets), AssetDbSource::assetFromDbResults);
    return walletAssets;
}

std::optional<Asset> AssetDbSource::getAsset(const size_t id) const {
    const auto assetFromDb = database->getAsset(id);
    if (assetFromDb.isNull()) return {};
    return this->assetFromDbResults(assetFromDb);
}

bool AssetDbSource::addAsset(const size_t walletId, const std::string& type,
                                   const std::string& description) {
    return database->addAsset(walletId, type, description);
}

} // my_wallets
