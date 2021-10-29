#pragma once

#include <vector>
#include <iostream>

#include "entity/asset.hpp"
#include "entity/asset_state.hpp"
#include "date_handling/date.hpp"

namespace my_wallets {
namespace model {

class BasicAssetStatisticModel {
public:
    BasicAssetStatisticModel(const Asset& asset, const std::vector<AssetState>& assetStates);
    friend std::ostream& operator<<(std::ostream& os, const BasicAssetStatisticModel& basicAssetStatisticModel) {
        os << "Asset: " << basicAssetStatisticModel.assetType << "\n";
        os << "Incomes: " << basicAssetStatisticModel.sumOfIncomes << "\n";
        os << "Current asset value: " << basicAssetStatisticModel.newestAssetValue << "\n";
        os << "Profit: " << basicAssetStatisticModel.newestAssetValue - basicAssetStatisticModel.sumOfIncomes << "\n";
        os << "\tDate, value, income, growth, growthInPercenet, growthInPercentScaleByYear" << "\n";
        for (const auto& stat : basicAssetStatisticModel.assetStateStats) {
            os << "\t" << stat.date.asString() << ", " << stat.value << ", " <<stat.income << ", "
                    << stat.growth << ", " << stat.growthInPercent << ", " << stat.growthInPercentScaledByYear << "\n";
        }
        return os;
    }

private:
    struct SingleAssetStateStat {
        Date date;
        double value;
        double income;
        double growth;
        double growthInPercent;
        double growthInPercentScaledByYear;
    };

    void calculateAssetStateStats(const std::vector<AssetState>& assetStates);
    void calculateSumOfIncomes(const std::vector<AssetState>& assetStates);
    void findNewestAssetValue(const std::vector<AssetState>& assetStates);

    std::string assetType;
    std::vector<SingleAssetStateStat> assetStateStats;
    double sumOfIncomes;
    double newestAssetValue;
};

} // model
} // my_wallest