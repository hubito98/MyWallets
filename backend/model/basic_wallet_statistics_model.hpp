#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "nlohmann/json.hpp"

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

    nlohmann::json toJson() const {
        nlohmann::json walletStatJson;
        walletStatJson["walletName"] = walletName;
        walletStatJson["wholeWalletValue"] = wholeWalletValue;
        std::vector<nlohmann::json> assetStatsJson;
        std::transform(assetStats.begin(), assetStats.end(), std::back_inserter(assetStatsJson),
                [](const SingleAssetStat& assetStat) {
            return assetStat.toJson();
        });
        walletStatJson["assetStats"] = assetStatsJson;
        return walletStatJson;
    }

private:
    struct SingleAssetStat {
        std::string type;
        double currentValue;
        double percentageOfTotal;

        nlohmann::json toJson() const {
            nlohmann::json statJson;
            statJson["type"] = type;
            statJson["currentValue"] = currentValue;
            statJson["percentageOfTotal"] = percentageOfTotal;
            return statJson;
        }
    };

    void calculateWholeWalletValue(const std::vector<AssetWithItsStates>& assetsWithStates);
    void calculateAssetStats(const std::vector<AssetWithItsStates>& assetsWithStates);

    std::string walletName;
    double wholeWalletValue;
    std::vector<SingleAssetStat> assetStats;
};

} // model
} // my_wallets