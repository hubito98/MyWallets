#pragma once

#include <iostream>

#include "frontend/my_wallets.hpp"


namespace my_wallets {
namespace cli {

class CLI {
public:
    CLI(std::unique_ptr<frontend::MyWallets> myWallets)
    : myWallets(std::move(myWallets)),
      running(false),
      currentState(State::USERS_MENU) {}

    void run() {
        running = true;
        while (running) {
            size_t choice;
            if (currentState == State::USERS_MENU) {
                showUsersMenu();
                std::cin>>choice;
                getEOFFromInputStream();
                if (choice == 1) {
                    addUserAction();
                } else if (choice == 2) {
                    selectUserAction();
                } else if (choice == 3) {
                    showUsersAction();
                } else {
                    break;
                }
            } else if (currentState == State::WALLETS_MENU) {
                showWalletsMenu();
                std::cin>>choice;
                getEOFFromInputStream();
                if (choice == 1) {
                    addWalletAction();
                } else if (choice == 2) {
                    selectWalletAction();
                } else if (choice == 3) {
                    showWalletsAction();
                } else if (choice == 0) {
                    backToUsersMenu();
                } else {
                    break;
                }
            } else if (currentState == State::ASSETS_MENU) {
                showAssetsMenu();
                std::cin>>choice;
                getEOFFromInputStream();
                if (choice == 1) {
                    addAssetAction();
                } else if (choice == 2) {
                    selectAssetAction();
                } else if (choice == 3) {
                    showAssetsAction();
                } else if (choice == 0) {
                    backToWalletsMenu();
                } else {
                    break;
                }
            } else if (currentState == State::ASSET_STATES_MENU) {
                showAssetStatesMenu();
                std::cin>>choice;
                getEOFFromInputStream();
                if (choice == 1) {
                    addAssetStateAction();
                } else if (choice == 2) {
                    showAssetStatesAction();
                } else if (choice == 3) {
                    showBasicAssetStatisticsAction();
                } else if (choice == 0) {
                    backToAssetsMenu();
                } else {
                    break;
                }
            }
        }
    }
private:
    enum class State { USERS_MENU, WALLETS_MENU, ASSETS_MENU, ASSET_STATES_MENU };

    void showUsersMenu() const {
        std::cout<<std::endl<<"1 - add new user"<<std::endl;
        std::cout<<"2 - select user"<<std::endl;
        std::cout<<"3 - show users"<<std::endl<<std::endl;
    }

    void addUserAction() const {
        std::string login;
        std::cout<<"login: ";
        std::getline(std::cin, login);
        std::cout<<std::endl;
        if (myWallets->addUser(login)) {
            std::cout<<"Succesfully added user with login: "<<login<<std::endl;
        } else {
            std::cout<<"Failed adding user with login: "<<login<<std::endl;
        }
    }

    void selectUserAction() {
        std::cout<<"Choose user:"<<std::endl;
        const auto users = myWallets->getUsers();
        for (size_t userNumber = 0; userNumber < users.size(); userNumber++) {
            std::cout<<userNumber<<" "<<users[userNumber]<<std::endl;
        }
        size_t choice;
        std::cin>>choice;
        getEOFFromInputStream();
        if (choice >= users.size()) {
            std::cout<<"Wrong choice"<<std::endl;
            currentState = State::USERS_MENU;
        } else {
            std::cout<<"You choosed: "<<users[choice]<<std::endl;
            choosedUser = std::make_unique<model::UserModel>(std::move(users[choice]));
            currentState = State::WALLETS_MENU;
        }
    }

    void showUsersAction() const {
        std::cout<<"Users:"<<std::endl;
        for (const auto& user : myWallets->getUsers()) {
            std::cout<<user<<std::endl;
        }
    }

    void showWalletsMenu() const {
        std::cout<<std::endl<<"1 - create wallet"<<std::endl;
        std::cout<<"2 - select wallet"<<std::endl;
        std::cout<<"3 - show wallets"<<std::endl;
        std::cout<<"0 - back to previous menu"<<std::endl<<std::endl;
    }

    void addWalletAction() const {
        std::string name, description;
        std::cout<<"name: ";
        std::getline(std::cin, name);
        std::cout<<std::endl;
        std::cout<<"description: ";
        std::getline(std::cin, description);
        std::cout<<std::endl;
        if (myWallets->addWallet(choosedUser->getLogin(), name, description)) {
            std::cout<<"Succesfully added wallet for user: "<<choosedUser->getLogin()<<std::endl;
        } else {
            std::cout<<"Failed adding wallet for user: "<<choosedUser->getLogin()<<std::endl;
        }
    }

    void selectWalletAction() {
        std::cout<<"Choose wallet:"<<std::endl;
        const auto wallets = myWallets->getUserWallets(*choosedUser);
        for (size_t walletNumber = 0; walletNumber < wallets.size(); walletNumber++) {
            std::cout<<walletNumber<<" "<<wallets[walletNumber]<<std::endl;
        }
        size_t choice;
        std::cin>>choice;
        getEOFFromInputStream();
        if (choice >= wallets.size()) {
            std::cout<<"Wrong choice"<<std::endl;
            currentState = State::WALLETS_MENU;
        } else {
            std::cout<<"You choosed: "<<wallets[choice]<<std::endl;
            choosedWallet = std::make_unique<model::WalletModel>(std::move(wallets[choice]));
            currentState = State::ASSETS_MENU;
        }
    }

    void showWalletsAction() const {
        std::cout<<"Wallets of "<<choosedUser->getLogin()<<":"<<std::endl;
        for (const auto& wallet : myWallets->getUserWallets(*choosedUser)) {
            std::cout<<wallet<<std::endl;
        }
    }

    void backToUsersMenu() {
        choosedUser.reset();
        currentState = State::USERS_MENU;
    }

    void showAssetsMenu() const {
        std::cout<<std::endl<<"1 - create asset"<<std::endl;
        std::cout<<"2 - select asset"<<std::endl;
        std::cout<<"3 - show assets"<<std::endl;
        std::cout<<"0 - back to previous menu"<<std::endl<<std::endl;
    }

    void addAssetAction() const {
        std::string type, description;
        std::cout<<"type: ";
        std::getline(std::cin, type);
        std::cout<<std::endl;
        std::cout<<"description: ";
        std::getline(std::cin, description);
        std::cout<<std::endl;
        if (myWallets->addAsset(choosedWallet->getId(), type, description)) {
            std::cout<<"Succesfully added asset to: "<<*choosedWallet<<std::endl;
        } else {
            std::cout<<"Failed adding asset to: "<<*choosedWallet<<std::endl;
        }
    }

    void selectAssetAction() {
        std::cout<<"Choose asset:"<<std::endl;
        const auto assets = myWallets->getAssetsFromWallet(*choosedWallet);
        for (size_t assetNumber = 0; assetNumber < assets.size(); assetNumber++) {
            std::cout<<assetNumber<<" "<<assets[assetNumber]<<std::endl;
        }
        size_t choice;
        std::cin>>choice;
        getEOFFromInputStream();
        if (choice >= assets.size()) {
            std::cout<<"Wrong choice"<<std::endl;
            currentState = State::ASSETS_MENU;
        } else {
            std::cout<<"You choosed: "<<assets[choice]<<std::endl;
            choosedAsset = std::make_unique<model::AssetModel>(std::move(assets[choice]));
            currentState = State::ASSET_STATES_MENU;
        }
    }

    void showAssetsAction() const {
        std::cout<<"Assets from "<<*choosedWallet<<":"<<std::endl;
        for (const auto& asset : myWallets->getAssetsFromWallet(*choosedWallet)) {
            std::cout<<asset<<std::endl;
        }
    }

    void backToWalletsMenu() {
        choosedWallet.reset();
        currentState = State::WALLETS_MENU;
    }

    void showAssetStatesMenu() const {
        std::cout<<std::endl<<"1 - create asset state"<<std::endl;
        std::cout<<"2 - show asset states"<<std::endl;
        std::cout<<"3 - show basic asset statistics"<<std::endl;
        std::cout<<"0 - back to previous menu"<<std::endl<<std::endl;
    }

    void addAssetStateAction() const {
        size_t year, month, day;
        double value, income;
        std::cout<<"year: ";
        std::cin>>year;
        getEOFFromInputStream();
        std::cout<<std::endl;
        std::cout<<"month: ";
        std::cin>>month;
        getEOFFromInputStream();
        std::cout<<std::endl;
        std::cout<<"day: ";
        std::cin>>day;
        getEOFFromInputStream();
        std::cout<<std::endl;
        std::cout<<"value: ";
        std::cin>>value;
        getEOFFromInputStream();
        std::cout<<std::endl;
        std::cout<<"income: ";
        std::cin>>income;
        getEOFFromInputStream();
        std::cout<<std::endl;
        if (myWallets->addAssetState(choosedAsset->getId(), {year, month, day}, value, income)) {
            std::cout<<"Succesfully added asset state of: "<<*choosedAsset<<std::endl;
        } else {
            std::cout<<"Failed adding asset state of: "<<*choosedAsset<<std::endl;
        }
    }

    void showAssetStatesAction() const {
        std::cout<<"Asset states of "<<*choosedAsset<<":"<<std::endl;
        for (const auto& assetState : myWallets->getAssetStatesOfAsset(*choosedAsset)) {
            std::cout<<assetState<<std::endl;
        }
    }
    void showBasicAssetStatisticsAction() const {
        std::cout<<myWallets->getBasicAssetStatistics(*choosedAsset)<<std::endl;
    }

    void backToAssetsMenu() {
        choosedAsset.reset();
        currentState = State::ASSETS_MENU;
    }

    void getEOFFromInputStream() const {
        char eof;
        std::cin.get(eof);
    }

    std::unique_ptr<frontend::MyWallets> myWallets;
    State currentState;
    std::unique_ptr<model::UserModel> choosedUser;
    std::unique_ptr<model::WalletModel> choosedWallet;
    std::unique_ptr<model::AssetModel> choosedAsset;
    bool running;
};

} // cli
} // my_wallets