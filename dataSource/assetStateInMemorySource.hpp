#pragma once

#include <vector>
#include <optional>

#include "dataSource/assetStateSource.hpp"
#include "entity/assetState.hpp"

class AssetStateInMemorySource : public AssetStateSource {
public:
    const std::vector<AssetState>&  getAssetStates() const override;
    const std::vector<AssetState> getParticularAssetStates(const size_t assetId) const override;
    std::optional<AssetState> getAssetState(const size_t id) const override;
    bool addAssetState(const size_t assetId, const Date& date, const double value,
                              const double income) override;
private:
    std::vector<AssetState> assetStates;
};
