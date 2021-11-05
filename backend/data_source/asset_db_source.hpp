#pragma once

#include <vector>
#include <optional>

#include <mysqlx/xdevapi.h>

#include "data_source/asset_source.hpp"
#include "entity/asset.hpp"
#include "data_source/database.hpp"

namespace my_wallets {

class AssetDbSource : public AssetSource {
public:
    AssetDbSource(std::shared_ptr<Database> database)
    : database(database) {}
    const std::vector<Asset>  getAssets() const override;
    const std::vector<Asset> getWalletAssets(const size_t walletId) const override;
    std::optional<Asset> getAsset(const size_t id) const override;
    bool addAsset(const size_t walletId, const std::string& type,
                  const std::string& description=0) override;
    bool removeAsset(const size_t id) override;
private:
    static Asset assetFromDbResults(mysqlx::Row userFromDb) {
        return Asset((int)userFromDb[0], (int)userFromDb[3],
                (std::string)userFromDb[1], (std::string)userFromDb[2]);
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
