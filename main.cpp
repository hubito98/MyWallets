#include <iostream>


#include "entity/user.hpp"
#include "entity/wallet.hpp"
#include "entity/asset.hpp"
#include "entity/asset_state.hpp"

#include "data_source/database.hpp"
#include "data_source/user_db_source.hpp"
#include "data_source/wallet_db_source.hpp"
#include "data_source/asset_db_source.hpp"
#include "data_source/asset_state_db_source.hpp"

#include "date_handling/date.hpp"

#include "my_wallets.hpp"

using namespace my_wallets;

void setup(MyWallets& myWallets) {
    myWallets.addUser("user1");
    myWallets.addUser("user2");

    const auto firstUserLogin = myWallets.getUsers()[0].getLogin();
    const auto secondUserLogin = myWallets.getUsers()[1].getLogin();
    myWallets.addWallet(firstUserLogin, "Poduszka finansowa", "Pieniadze na czarna godzine");
    myWallets.addWallet(firstUserLogin, "Dlugoterminowy", "Oszczednosci na emeryture");
    myWallets.addWallet(secondUserLogin, "Wklad na kredyt hipoteczny", "Pieniadze na wklad na mieszkanie");

    const auto firstWalletId = 1;
    const auto secondWalletId = 2;
    const auto thirdWalletId = 3;
    myWallets.addAsset(firstWalletId, "Lokaty", "Niskoprocentowe lokaty (najbezpiecznieszy element)");
    myWallets.addAsset(firstWalletId, "Obligacje EDO", "Obligacje 10 letnie indeksowane inflacja");
    myWallets.addAsset(secondWalletId, "ETF EM", "Pasywny fundusz akcyjny firm panstw wschodzacych");
    myWallets.addAsset(secondWalletId, "ETF DM", "Pasywny fundusz akcyjny firm panstw rozwinietych");
    myWallets.addAsset(secondWalletId, "Zloto", "Zloto inwestycyjne (monety i sztabki)");
    myWallets.addAsset(thirdWalletId, "Gotowka", "Gotowka odkladana na wklad wlasny na kredyt hipoteczny");

    const auto firstAssetId = 1;
    const auto secondAssetId = 2;
    myWallets.addAssetState(firstAssetId, Date(2021, 8, 13), 100, 100);
    myWallets.addAssetState(firstAssetId, Date(2021, 9, 10), 1605.22, 1500);
    myWallets.addAssetState(secondAssetId, Date(2021, 8, 13), 1000, 1000);
    myWallets.addAssetState(secondAssetId, Date(2021, 8, 28), 1002.21, 0);
    myWallets.addAssetState(secondAssetId, Date(2021, 9, 10), 2004.26, 1000);
}


int main() {
    std::shared_ptr<Database> database(new Database("test_db"));
    MyWallets myWallets(std::make_unique<UserDbSource>(database),
                        std::make_unique<WalletDbSource>(database),
                        std::make_unique<AssetDbSource>(database),
                        std::make_unique<AssetStateDbSource>(database));
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