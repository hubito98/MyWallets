#pragma once

#include <vector>
#include <optional>

#include <cppconn/resultset.h>

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
    static Asset assetFromDbResults(sql::ResultSet* userFromDb) {
        return Asset(userFromDb->getInt(1), userFromDb->getInt(4),
                userFromDb->getString(2), userFromDb->getString(3));
    }

    std::shared_ptr<Database> database;
};

} // my_wallets
