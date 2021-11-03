#include "basic_wallet_statistics_model.hpp"

#include <numeric>


namespace my_wallets {
namespace model {


BasicWalletStatisticsModel::BasicWalletStatisticsModel(const Wallet& wallet, const std::vector<AssetWithItsStates>& assetsWithStates) noexcept {
    walletName = wallet.getName();
    if (assetsWithStates.empty()) {
        wholeWalletValue = 0;
    } else {
        calculateWholeWalletValue(assetsWithStates);
        calculateAssetStats(assetsWithStates);
    }
}

void BasicWalletStatisticsModel::calculateWholeWalletValue(const std::vector<AssetWithItsStates>& assetsWithStates) {
    wholeWalletValue = std::transform_reduce(assetsWithStates.begin(), assetsWithStates.end(), static_cast<double>(0),
            std::plus<double>(), [](const AssetWithItsStates& assetWithItsStates) {
            const auto [asset, assetStates] = assetWithItsStates;
            if (assetStates.empty()) {
                return static_cast<double>(0);
            } else {
                return assetStates[0].getValue();
            }
        });
}

void BasicWalletStatisticsModel::calculateAssetStats(const std::vector<AssetWithItsStates>& assetsWithStates) {
    std::transform(assetsWithStates.begin(), assetsWithStates.end(), std::back_inserter(assetStats),
            [this](const AssetWithItsStates& assetWithItsStates) {
        const auto [asset, assetStates] = assetWithItsStates;
        const auto assetType = asset.getType();
        const auto currentValue = assetStates.empty() ? 0 : assetStates[0].getValue();
        const auto percentageOfTotal = this->wholeWalletValue == 0 ? 0 : currentValue / this->wholeWalletValue * 100;
        return SingleAssetStat{
            .type = assetType,
            .currentValue = currentValue,
            .percentageOfTotal = percentageOfTotal};
    });
}

} // model
} // my_wallets