#include "asset_state_db_source.hpp"

namespace my_wallets {

const std::vector<AssetState> AssetStateDbSource::getAssetStates() const {
    std::vector<AssetState> assetStates;
    auto assetStatesFromDb = database->getAssetStates();
    std::transform(assetStatesFromDb.begin(), assetStatesFromDb.end(), std::back_inserter(assetStates), AssetStateDbSource::assetStateFromDbResult);
    return assetStates;
}

const std::vector<AssetState> AssetStateDbSource::getParticularAssetStates(const size_t assetId) const {
    std::vector<AssetState> particularAssetStates;
    auto assetStatesFromDb = database->getParticularAssetStates(assetId);
    std::transform(assetStatesFromDb.begin(), assetStatesFromDb.end(), std::back_inserter(particularAssetStates), AssetStateDbSource::assetStateFromDbResult);
    return particularAssetStates;
}

std::optional<AssetState> AssetStateDbSource::getAssetState(const size_t id) const {
    const auto assetStateFromDb = database->getAssetState(id);
    if (assetStateFromDb.isNull()) return {};
    return this->assetStateFromDbResult(assetStateFromDb);
}

bool AssetStateDbSource::addAssetState(const size_t assetId, const Date& date, const double value,
                                             const double income) {
    return database->addAssetState(assetId, date.getYear(), date.getMonth(), date.getDay(), value, income);
}

} // my_wallets
