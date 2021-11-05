#pragma once

#include <vector>
#include <optional>

#include <mysqlx/xdevapi.h>

#include "data_source/asset_state_source.hpp"
#include "entity/asset_state.hpp"
#include "data_source/database.hpp"

namespace my_wallets {

class AssetStateDbSource : public AssetStateSource {
public:
    AssetStateDbSource(std::shared_ptr<Database> database)
    : database(database) {};
    const std::vector<AssetState>  getAssetStates() const override;
    const std::vector<AssetState> getParticularAssetStates(const size_t assetId) const override;
    std::optional<AssetState> getAssetState(const size_t id) const override;
    bool addAssetState(const size_t assetId, const Date& date, const double value,
                              const double income) override;
    bool removeAssetState(const size_t id) override;
private:
    static AssetState assetStateFromDbResult(const mysqlx::Row& assetStateFromDb) {
        Date assetStateDate((int)assetStateFromDb[1], (int)assetStateFromDb[2], (int)assetStateFromDb[3]);
        return AssetState((int)assetStateFromDb[0], (int)assetStateFromDb[6], std::move(assetStateDate),
                (double)assetStateFromDb[4], (double)assetStateFromDb[5]);
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
