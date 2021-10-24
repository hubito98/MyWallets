#pragma once

#include <vector>
#include <optional>
#include "entity/asset_state.hpp"

namespace my_wallets {

class AssetStateSource {
public:
    virtual const std::vector<AssetState>  getAssetStates() const = 0;
    virtual const std::vector<AssetState> getParticularAssetStates(const size_t assetId) const = 0;
    virtual std::optional<AssetState> getAssetState(const size_t id) const = 0;
    virtual bool addAssetState(const size_t assetId, const Date& date, const double value,
                               const double income) = 0;
};

} // my_wallets
