#include <iostream>


#include "entity/user.hpp"
#include "entity/wallet.hpp"
#include "entity/asset.hpp"
#include "entity/assetState.hpp"

#include "dataSource/userInMemorySource.hpp"
#include "dataSource/walletInMemorySource.hpp"
#include "dataSource/assetInMemorySource.hpp"
#include "dataSource/assetStateInMemorySource.hpp"

#include "dateHandling/date.hpp"


void setup(UserInMemorySource& userSource, WalletInMemorySource& walletSource,
           AssetInMemorySource& assetSource, AssetStateInMemorySource& assetStateSource) {
    userSource.addUser("user1");
    userSource.addUser("user2");

    const auto firstUserLogin = userSource.getUsers()[0].getLogin();
    const auto secondUserLogin = userSource.getUsers()[1].getLogin();
    walletSource.addWallet(firstUserLogin, "Poduszka finansowa", "Pieniadze na czarna godzine");
    walletSource.addWallet(firstUserLogin, "Dlugoterminowy", "Oszczednosci na emeryture");
    walletSource.addWallet(secondUserLogin, "Wklad na kredyt hipoteczny", "Pieniadze na wklad na mieszkanie");

    const auto firstWalletId = walletSource.getWallets()[0].getId();
    const auto secondWalletId = walletSource.getWallets()[1].getId();
    const auto thirdWalletId = walletSource.getWallets()[2].getId();
    assetSource.addAsset(firstWalletId, "Lokaty", "Niskoprocentowe lokaty (najbezpiecznieszy element)");
    assetSource.addAsset(firstWalletId, "Obligacje EDO", "Obligacje 10 letnie indeksowane inflacja");
    assetSource.addAsset(secondWalletId, "ETF EM", "Pasywny fundusz akcyjny firm panstw wschodzacych");
    assetSource.addAsset(secondWalletId, "ETF DM", "Pasywny fundusz akcyjny firm panstw rozwinietych");
    assetSource.addAsset(secondWalletId, "Zloto", "Zloto inwestycyjne (monety i sztabki)");
    assetSource.addAsset(thirdWalletId, "Gotowka", "Gotowka odkladana na wklad wlasny na kredyt hipoteczny");

    const auto firstAssetId = assetSource.getAssets()[0].getId();
    const auto secondAssetId = assetSource.getAssets()[1].getId();
    assetStateSource.addAssetState(firstAssetId, Date(2021, 8, 13), 100, 100);
    assetStateSource.addAssetState(firstAssetId, Date(2021, 9, 10), 1605.22, 1500);
    assetStateSource.addAssetState(secondAssetId, Date(2021, 8, 13), 1000, 1000);
    assetStateSource.addAssetState(secondAssetId, Date(2021, 8, 28), 1002.21, 0);
    assetStateSource.addAssetState(secondAssetId, Date(2021, 9, 10), 2004.26, 1000);
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
    std::cout<<"AssetState: "<<assetState.getId()<<", "<<assetState.getAssetId()<<", "<<assetState.getDate()<<", "
            <<assetState.getValue()<<", "<<assetState.getIncome()<<std::endl;
}

int main() {
    UserInMemorySource userSource;
    WalletInMemorySource walletSource;
    AssetInMemorySource assetSource;
    AssetStateInMemorySource assetStateSource;
    setup(userSource, walletSource, assetSource, assetStateSource);

    for (const auto& user : userSource.getUsers()) {
        printUser(user);
        for (const auto& userWallet : walletSource.getUserWallets(user.getLogin())) {
            std::cout<<"\t";
            printWallet(userWallet);
            for (const auto& walletAsset : assetSource.getWalletAssets(userWallet.getId())) {
                std::cout<<"\t\t";
                printAsset(walletAsset);
                for (const auto& assetState : assetStateSource.getParticularAssetStates(walletAsset.getId())) {
                    std::cout<<"\t\t\t";
                    printAssetState(assetState);
                }
            }
        }
    }
    std::cout<<std::endl;    
}