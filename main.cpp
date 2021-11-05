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
#include "rest/rest.hpp"

using namespace my_wallets;


int main() {
    std::shared_ptr<Database> database = 
            std::make_shared<Database>(utils::getEnv(utils::DatabaseNameEnvVar::envName, utils::DatabaseNameEnvVar::defaultValue));
    const std::string executeType = utils::getEnv(utils::ExecuteTypeEnvVar::envName, utils::ExecuteTypeEnvVar::defaultValue);
    if (executeType == "cli") {
        cli::CLI cli(std::make_unique<frontend::MyWallets>(std::make_unique<UserDbSource>(database),
                                                        std::make_unique<WalletDbSource>(database),
                                                        std::make_unique<AssetDbSource>(database),
                                                        std::make_unique<AssetStateDbSource>(database)));
        cli.run();
    } else if (executeType == "rest") {
        rest::RESTServer server(std::make_unique<frontend::MyWallets>(std::make_unique<UserDbSource>(database),
                                                        std::make_unique<WalletDbSource>(database),
                                                        std::make_unique<AssetDbSource>(database),
                                                        std::make_unique<AssetStateDbSource>(database)));
        server.run();
    } else {
        std::cout<<"Invalid value of "<< utils::ExecuteTypeEnvVar::envName <<" flag"<<std::endl;
    }
}