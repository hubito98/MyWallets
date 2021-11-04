#pragma once

#include <vector>
#include <memory>

#include "data_source/asset_source.hpp"
#include "data_source/asset_state_source.hpp"
#include "data_source/user_source.hpp"
#include "data_source/wallet_source.hpp"

#include "model/user_model.hpp"
#include "model/wallet_model.hpp"
#include "model/asset_model.hpp"
#include "model/asset_state_model.hpp"
#include "model/basic_asset_statistics_model.hpp"
#include "model/basic_wallet_statistics_model.hpp"

namespace my_wallets {
namespace frontend {

using UserModel = model::UserModel;
using WalletModel = model::WalletModel;
using AssetModel = model::AssetModel;
using AssetStateModel = model::AssetStateModel;

class MyWallets {
public:
    MyWallets(std::unique_ptr<UserSource> userSource, std::unique_ptr<WalletSource> walletSource,
              std::unique_ptr<AssetSource> assetSource, std::unique_ptr<AssetStateSource> assetStateSource)
    : assetSource(std::move(assetSource)),
      assetStateSource(std::move(assetStateSource)),
      userSource(std::move(userSource)),
      walletSource(std::move(walletSource)) {}
    const std::vector<UserModel> getUsers() const;
    bool addUser(const std::string& login);
    bool removeUser(const UserModel& user);
    const std::vector<WalletModel> getUserWallets(const UserModel& userModel) const;
    bool addWallet(const std::string& userLogin, const std::string& name,
                   const std::string& description="");
    bool removeWallet(const WalletModel& wallet);
    const std::vector<AssetModel> getAssetsFromWallet(const WalletModel& walletModel) const;
    bool addAsset(const size_t walletId, const std::string& type,
                  const std::string& description=0);
    bool removeAsset(const AssetModel& asset);
    const std::vector<AssetStateModel> getAssetStatesOfAsset(const AssetModel& assetModel) const;
    bool addAssetState(const size_t assetId, const Date& date, const double value,
                       const double income);
    bool removeAssetState(const AssetStateModel& assetState);
    
    // asset states statistics    
    const model::BasicAssetStatisticModel getBasicAssetStatistics(const AssetModel& assetModel) const;
    const model::BasicWalletStatisticsModel getBasicWalletStatistics(const WalletModel& walletModel) const;

private:
    std::unique_ptr<UserSource> userSource;
    std::unique_ptr<WalletSource> walletSource;
    std::unique_ptr<AssetSource> assetSource;
    std::unique_ptr<AssetStateSource> assetStateSource;
};

} // frontend
} // my_wallets
