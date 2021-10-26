#include "data_source/asset_in_memory_source.hpp"

namespace my_wallets {

const std::vector<Asset> AssetInMemorySource::getAssets() const {
    return assets;
}

const std::vector<Asset> AssetInMemorySource::getWalletAssets(const size_t walletId) const {
    std::vector<Asset> walletAssets;
    std::copy_if(assets.begin(), assets.end(), std::back_inserter(walletAssets), [walletId](const Asset& asset){
        return asset.getWalletId() == walletId;
    });
    return walletAssets;
}

std::optional<Asset> AssetInMemorySource::getAsset(const size_t id) const {
    auto foundAsset = std::find_if(assets.begin(), assets.end(), [id](const Asset& asset){
        return asset.getId() == id;
    });
    if (foundAsset == assets.end()) return {};
    return *foundAsset;
}

bool AssetInMemorySource::addAsset(const size_t walletId, const std::string& type,
                                   const std::string& description) {
    assets.push_back(Asset(assets.size()+1, walletId, type, description));
    return true;
}

} // my_wallets
