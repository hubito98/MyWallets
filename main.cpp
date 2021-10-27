#include <iostream>

#include "utils/envs.hpp"

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

#include "frontend/my_wallets.hpp"
#include "cli/cli.hpp"

using namespace my_wallets;


int main() {
    std::shared_ptr<Database> database = 
            std::make_shared<Database>(utils::getEnv(utils::DatabaseNameEnvVar::envName, utils::DatabaseNameEnvVar::defaultValue));
    frontend::MyWallets myWallets(std::make_unique<UserDbSource>(database),
                                  std::make_unique<WalletDbSource>(database),
                                  std::make_unique<AssetDbSource>(database),
                                  std::make_unique<AssetStateDbSource>(database));
    cli::CLI cli(std::make_unique<frontend::MyWallets>(std::make_unique<UserDbSource>(database),
                                                       std::make_unique<WalletDbSource>(database),
                                                       std::make_unique<AssetDbSource>(database),
                                                       std::make_unique<AssetStateDbSource>(database)));
    cli.run();
}