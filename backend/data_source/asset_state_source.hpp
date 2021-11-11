#pragma once

#include <vector>
#include <optional>
#include "entity/asset_state.hpp"

namespace my_wallets {

class AssetStateSource {
public:
    virtual const std::vector<AssetState>  getDescendingAssetStates() const = 0;
    virtual const std::vector<AssetState> getParticularAssetDescendingStates(const size_t assetId) const = 0;
    virtual std::optional<AssetState> getAssetState(const size_t id) const = 0;
    virtual bool addAssetState(const size_t assetId, const Date& date, const double value,
                               const double income) = 0;
    virtual bool removeAssetState(const size_t id) = 0;
    virtual ~AssetStateSource() {};
};

} // my_wallets
