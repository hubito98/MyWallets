#include "model/basic_asset_statistics_model.hpp"

#include <numeric>

namespace my_wallets {
namespace model {

BasicAssetStatisticModel::BasicAssetStatisticModel(const Asset& asset, const std::vector<AssetState>& assetStates) {
    assetType = asset.getType();
    if (assetStates.size() == 0) {
        sumOfIncomes = 0;
        newestAssetValue = 0;
    } else {
        calculateAssetStateStats(assetStates);
        calculateSumOfIncomes(assetStates);
        findNewestAssetValue(assetStates);
    }
}

void BasicAssetStatisticModel::calculateAssetStateStats(const std::vector<AssetState>& assetStates) {
    const auto& newestIt = assetStates.cbegin();
    const auto& oldestIt = assetStates.cend();
    std::transform(newestIt, oldestIt-1, newestIt+1, std::back_inserter(this->assetStateStats),
            [](const AssetState& current, const AssetState& previous) {
        double growth = (current.getValue() - current.getIncome()) - previous.getValue();
        double growthInPercent = growth / previous.getValue() * 100;
        int daysDifference = std::min(current.getDate() - previous.getDate(), 1);
        return SingleAssetStateStat{
            .date = current.getDate(),
            .value = current.getValue(),
            .income = current.getIncome(),
            .growth = growth,
            .growthInPercent = growthInPercent,
            .growthInPercentScaledByYear = static_cast<double>(365)/daysDifference * growthInPercent};
    });
    // add oldest asset state to the end of stats
    const auto& oldestAssetState = assetStates.back();
    double growth = oldestAssetState.getValue() - oldestAssetState.getIncome(); 
    this->assetStateStats.push_back(SingleAssetStateStat{
        .date = oldestAssetState.getDate(),
        .value = oldestAssetState.getValue(),
        .income = oldestAssetState.getIncome(),
        .growth = growth,
        .growthInPercent = growth / oldestAssetState.getValue(),
        .growthInPercentScaledByYear = 0});
}

void BasicAssetStatisticModel::calculateSumOfIncomes(const std::vector<AssetState>& assetStates) {
    this->sumOfIncomes = std::transform_reduce(assetStates.begin(), assetStates.end(),
                                               static_cast<double>(0), std::plus<double>(),
                                               [](const AssetState& assetState) {
        return assetState.getIncome();
    });
}

void BasicAssetStatisticModel::findNewestAssetValue(const std::vector<AssetState>& assetStates) {
    this->newestAssetValue = assetStates[0].getValue();
}

} // model
} // my_wallets