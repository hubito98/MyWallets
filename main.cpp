#include <iostream>

#include "dataSource/userInMemorySource.hpp"
#include "dataSource/walletInMemorySource.hpp"

int main() {
    UserInMemorySource userSource;
    auto users = userSource.getUsers();
    std::cout<<"Users number: "<<users.size()<<std::endl;
    std::cout<<"First user login: "<<users[0].getLogin()<<std::endl<<std::endl;

    WalletInMemorySource walletSource;
    auto wallets = walletSource.getWallets();
    std::cout<<"Wallets number: "<<wallets.size()<<std::endl;
    std::cout<<"First wallet info: "<<wallets[0].getId()<<", "<<wallets[0].getUserLogin()<<", "
             <<wallets[0].getName()<<", "<<wallets[0].getDescription()<<std::endl<<std::endl;
    auto userWallets = walletSource.getUserWallets(users[0].getLogin());
    std::cout<<"User wallets number: "<<userWallets.size()<<std::endl;
    std::cout<<"User first wallet info: "<<userWallets[0].getId()<<", "<<userWallets[0].getUserLogin()<<", "
             <<userWallets[0].getName()<<", "<<userWallets[0].getDescription()<<std::endl<<std::endl;
    
    walletSource.addWallet(users[0].getLogin(), "Dlugoterminowy");
    userWallets = walletSource.getUserWallets(users[0].getLogin());
    std::cout<<"User wallets number: "<<userWallets.size()<<std::endl;
    std::cout<<"User second wallet info: "<<userWallets[1].getId()<<", "<<userWallets[1].getUserLogin()<<", "
             <<userWallets[1].getName()<<", "<<userWallets[1].getDescription()<<std::endl<<std::endl;
}