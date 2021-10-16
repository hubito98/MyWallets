#pragma once

#include <vector>
#include <optional>

#include "dataSource/assetSource.hpp"
#include "entity/asset.hpp"

class AssetInMemorySource : public AssetSource {
public:
    const std::vector<Asset>&  getAssets() const override;
    const std::vector<Asset> getWalletAssets(const size_t walletId) const override;
    std::optional<Asset> getAsset(const size_t id) const override;
    bool addAsset(const size_t walletId, const std::string& type,
                  const std::string& description=0) override;
private:
    std::vector<Asset> assets;
};
