#include "asset_state_db_source.hpp"

namespace my_wallets {

const std::vector<AssetState> AssetStateDbSource::getDescendingAssetStates() const {
    std::vector<AssetState> assetStates;
    auto assetStatesFromDb = database->getOrderedAssetStates(Database::Order::DESC);
    if (assetStatesFromDb != nullptr) {
        while (assetStatesFromDb->next()) {
            assetStates.push_back(assetStateFromDbResult(assetStatesFromDb.get()));
        }
    }
    return assetStates;
}

const std::vector<AssetState> AssetStateDbSource::getParticularAssetDescendingStates(const size_t assetId) const {
    std::vector<AssetState> particularAssetStates;
    auto assetStatesFromDb = database->getParticularAssetOrderedStates(assetId, Database::Order::DESC);
    if (assetStatesFromDb != nullptr) {
        while (assetStatesFromDb->next()) {
            particularAssetStates.push_back(assetStateFromDbResult(assetStatesFromDb.get()));
        }
    }
    return particularAssetStates;
}

std::optional<AssetState> AssetStateDbSource::getAssetState(const size_t id) const {
    const auto assetStateFromDb = database->getAssetState(id);
    if (assetStateFromDb->next()) {
        return assetStateFromDbResult(assetStateFromDb.get());
    }
    return {};
}

bool AssetStateDbSource::addAssetState(const size_t assetId, const Date& date, const double value,
                                             const double income) {
    return database->addAssetState(assetId, date.getYear(), date.getMonth(), date.getDay(), value, income);
}

bool AssetStateDbSource::removeAssetState(const size_t id) {
    return database->removeAssetState(id);
}

} // my_wallets
