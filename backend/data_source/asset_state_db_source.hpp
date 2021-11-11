#pragma once

#include <vector>
#include <optional>

#include <cppconn/resultset.h>

#include "data_source/asset_state_source.hpp"
#include "entity/asset_state.hpp"
#include "data_source/database.hpp"

namespace my_wallets {

class AssetStateDbSource : public AssetStateSource {
public:
    AssetStateDbSource(std::shared_ptr<Database> database)
    : database(database) {};
    const std::vector<AssetState>  getDescendingAssetStates() const override;
    const std::vector<AssetState> getParticularAssetDescendingStates(const size_t assetId) const override;
    std::optional<AssetState> getAssetState(const size_t id) const override;
    bool addAssetState(const size_t assetId, const Date& date, const double value,
                              const double income) override;
    bool removeAssetState(const size_t id) override;
private:
    static AssetState assetStateFromDbResult(const sql::ResultSet* assetStateFromDb) {
        Date assetStateDate(assetStateFromDb->getInt(2), assetStateFromDb->getInt(3), assetStateFromDb->getInt(4));
        return AssetState(assetStateFromDb->getInt(1), assetStateFromDb->getInt(7), std::move(assetStateDate),
                assetStateFromDb->getDouble(5), assetStateFromDb->getDouble(6));
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
