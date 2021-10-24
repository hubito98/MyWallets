#include <iostream>


#include "entity/user.hpp"
#include "entity/wallet.hpp"
#include "entity/asset.hpp"
#include "entity/asset_state.hpp"

#include "data_source/user_in_memory_source.hpp"
#include "data_source/wallet_in_memory_source.hpp"
#include "data_source/asset_in_memory_source.hpp"
#include "data_source/asset_state_in_memory_source.hpp"

#include "date_handling/date.hpp"

#include "my_wallets.hpp"
// #include "data_source/database.hpp"

using namespace my_wallets;

void setup(MyWallets& myWallets) {
    myWallets.addUser("user1");
    myWallets.addUser("user2");

    const auto firstUserLogin = myWallets.getUsers()[0].getLogin();
    const auto secondUserLogin = myWallets.getUsers()[1].getLogin();
    myWallets.addWallet(firstUserLogin, "Poduszka finansowa", "Pieniadze na czarna godzine");
    myWallets.addWallet(firstUserLogin, "Dlugoterminowy", "Oszczednosci na emeryture");
    myWallets.addWallet(secondUserLogin, "Wklad na kredyt hipoteczny", "Pieniadze na wklad na mieszkanie");

    const auto firstWalletId = 0;
    const auto secondWalletId = 1;
    const auto thirdWalletId = 2;
    myWallets.addAsset(firstWalletId, "Lokaty", "Niskoprocentowe lokaty (najbezpiecznieszy element)");
    myWallets.addAsset(firstWalletId, "Obligacje EDO", "Obligacje 10 letnie indeksowane inflacja");
    myWallets.addAsset(secondWalletId, "ETF EM", "Pasywny fundusz akcyjny firm panstw wschodzacych");
    myWallets.addAsset(secondWalletId, "ETF DM", "Pasywny fundusz akcyjny firm panstw rozwinietych");
    myWallets.addAsset(secondWalletId, "Zloto", "Zloto inwestycyjne (monety i sztabki)");
    myWallets.addAsset(thirdWalletId, "Gotowka", "Gotowka odkladana na wklad wlasny na kredyt hipoteczny");

    const auto firstAssetId = 0;
    const auto secondAssetId = 1;
    myWallets.addAssetState(firstAssetId, Date(2021, 8, 13), 100, 100);
    myWallets.addAssetState(firstAssetId, Date(2021, 9, 10), 1605.22, 1500);
    myWallets.addAssetState(secondAssetId, Date(2021, 8, 13), 1000, 1000);
    myWallets.addAssetState(secondAssetId, Date(2021, 8, 28), 1002.21, 0);
    myWallets.addAssetState(secondAssetId, Date(2021, 9, 10), 2004.26, 1000);
}

void printUser(const User& user) {
    std::cout<<"User: "<<user.getLogin()<<std::endl;
}

void printWallet(const Wallet& wallet) {
    std::cout<<"Wallet: "<<wallet.getId()<<", "<<wallet.getUserLogin()<<", "<<wallet.getName()<<", "<<wallet.getDescription()<<std::endl;
}

void printAsset(const Asset& asset) {
    std::cout<<"Asset: "<<asset.getId()<<", "<<asset.getWalletId()<<", "<<asset.getType()<<", "<<asset.getDescription()<<std::endl;
}

void printAssetState(const AssetState& assetState) {
    std::cout<<"AssetState: "<<assetState.getId()<<", "<<assetState.getAssetId()<<", "<<assetState.getDate().asString()<<", "
            <<assetState.getValue()<<", "<<assetState.getIncome()<<std::endl;
}

int main() {
    std::shared_ptr<UserSource> userSource = std::make_shared<UserInMemorySource>();
    std::shared_ptr<WalletSource> walletSource = std::make_shared<WalletInMemorySource>();
    std::shared_ptr<AssetSource> assetSource = std::make_shared<AssetInMemorySource>();
    std::shared_ptr<AssetStateSource> assetStateSource = std::make_shared<AssetStateInMemorySource>();
    MyWallets myWallets(userSource, walletSource, assetSource, assetStateSource);
    setup(myWallets);

    for (const auto& user : myWallets.getUsers()) {
        std::cout<<user<<std::endl;
        for (const auto& userWallet : myWallets.getUserWallets(user)) {
            std::cout<<"\t"<<userWallet<<std::endl;
            for (const auto& walletAsset : myWallets.getAssetsFromWallet(userWallet)) {
                std::cout<<"\t\t"<<walletAsset<<std::endl;
                for (const auto& assetState : myWallets.getAssetStatesOfAsset(walletAsset)) {
                    std::cout<<"\t\t\t"<<assetState<<std::endl;
                }
            }
        }
    }
    std::cout<<std::endl;
}