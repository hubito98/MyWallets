#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "entity/wallet.hpp"
#include "entity/asset.hpp"
#include "entity/asset_state.hpp"

namespace my_wallets {
namespace model {

class BasicWalletStatisticsModel {
public:
    using AssetWithItsStates = std::pair<const Asset, const std::vector<AssetState>>;
  
    BasicWalletStatisticsModel(const Wallet& wallet, const std::vector<AssetWithItsStates>& assetsWithStates) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const BasicWalletStatisticsModel& basicWalletStatisticsModel) {
        os << "Wallet: " << basicWalletStatisticsModel.walletName << "\n";
        os << "Wallet value: " << basicWalletStatisticsModel.wholeWalletValue << "\n";
        os << "\tAsset type, current value, percentage of wallet value\n";
        for (const SingleAssetStat& singleAssetState : basicWalletStatisticsModel.assetStats) {
            os << "\t" << singleAssetState.type << ", " << singleAssetState.currentValue << ", "
                    << singleAssetState.percentageOfTotal << "%\n";
        }
        return os;
    }
private:
    struct SingleAssetStat {
        std::string type;
        double currentValue;
        double percentageOfTotal;
    };

    void calculateWholeWalletValue(const std::vector<AssetWithItsStates>& assetsWithStates);
    void calculateAssetStats(const std::vector<AssetWithItsStates>& assetsWithStates);

    std::string walletName;
    double wholeWalletValue;
    std::vector<SingleAssetStat> assetStats;
};

} // model
} // my_wallets