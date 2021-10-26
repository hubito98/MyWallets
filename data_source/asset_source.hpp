#pragma once

#include <vector>
#include <optional>
#include "entity/asset.hpp"

namespace my_wallets {

class AssetSource {
public:
    virtual const std::vector<Asset>  getAssets() const = 0;
    virtual const std::vector<Asset> getWalletAssets(const size_t walletId) const = 0;
    virtual std::optional<Asset> getAsset(const size_t id) const = 0;
    virtual bool addAsset(const size_t walletId, const std::string& type,
                          const std::string& description=0) = 0;
    virtual ~AssetSource() {};
};

} // my_wallets
