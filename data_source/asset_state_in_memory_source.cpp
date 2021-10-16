#include "asset_state_in_memory_source.hpp"

namespace my_wallets {

const std::vector<AssetState>& AssetStateInMemorySource::getAssetStates() const {
    return assetStates;
}

const std::vector<AssetState> AssetStateInMemorySource::getParticularAssetStates(const size_t assetId) const {
    std::vector<AssetState> foundStates;
    std::copy_if(assetStates.begin(), assetStates.end(), std::back_inserter(foundStates),
                 [assetId](const AssetState& state){
        return state.getAssetId() == assetId;
    });
    return foundStates;
}

std::optional<AssetState> AssetStateInMemorySource::getAssetState(const size_t id) const {
    auto foundAssetState = std::find_if(assetStates.begin(), assetStates.end(), [id](const AssetState& state){
        return state.getId() == id;
    });
    if (foundAssetState == assetStates.end()) return {};
    return *foundAssetState;
}

bool AssetStateInMemorySource::addAssetState(const size_t assetId, const Date& date, const double value,
                                             const double income) {
    assetStates.push_back(AssetState(assetStates.size(), assetId, date, value, income));
    return true;
}

} // my_wallets
