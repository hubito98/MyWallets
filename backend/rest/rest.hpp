#pragma once

#include <string>

#include <served/served.hpp>
#include "nlohmann/json.hpp"

#include "frontend/my_wallets.hpp"


namespace my_wallets {
namespace rest {

class RESTServer {
public:
    RESTServer(std::unique_ptr<frontend::MyWallets> myWallets)
    : myWallets(std::move(myWallets)), server("localhost", "8080", multiplexer) {
        setupEndpoints();
    }

    void setupEndpoints() {
        multiplexer.handle("/users/{login}")
            .get([this](served::response& res, const served::request& req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                const std::string login = req.params["login"];
                const auto user = this->myWallets->getUser(login);
                nlohmann::json result;
                if (user.has_value()) {
                    result["user"] = user->toJson();
                    std::vector<nlohmann::json> userWallets;
                    for (const auto& wallet : this->myWallets->getUserWallets(user.value())) {
                        userWallets.push_back(wallet.toJson());
                    }
                    result["wallets"] = userWallets;
                }
                res << result.dump();
            });
        multiplexer.handle("/users")
            .get([this](served::response & res, const served::request & req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                std::vector<nlohmann::json> users;
                for (const auto& user : this->myWallets->getUsers()) {
                    users.push_back(user.toJson());
                }
                nlohmann::json result;
                result["users"] = users;
                res << result.dump();
            })
            .post([this](served::response & res, const served::request & req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                nlohmann::json userInputJson = nlohmann::json::parse(req.body());
                std::cout<<req.body()<<std::endl;
                if (userInputJson["login"] != nullptr) {
                    this->myWallets->addUser(userInputJson["login"]);
                }
            });
        multiplexer.handle("/wallets/{id:\\d+}")
            .get([this](served::response& res, const served::request& req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                const auto walletId = std::stoi(req.params["id"]);
                const auto wallet = this->myWallets->getWallet(walletId);
                nlohmann::json result;
                if (wallet.has_value()) {
                    result["wallet"] = wallet->toJson();
                    std::vector<nlohmann::json> assetsFromWallet;
                    for (const auto& asset : this->myWallets->getAssetsFromWallet(wallet.value())) {
                        assetsFromWallet.push_back(asset.toJson());
                    }
                    result["assets"] = assetsFromWallet;
                }
                res << result.dump();
            });
        multiplexer.handle("/assets/{id:\\d+}")
            .get([this](served::response& res, const served::request& req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                const auto assetId = std::stoi(req.params["id"]);
                const auto asset = this->myWallets->getAsset(assetId);
                nlohmann::json result;
                if (asset.has_value()) {
                    result["asset"] = asset->toJson();
                    std::vector<nlohmann::json> assetStates;
                    for (const auto& assetState : this->myWallets->getAssetStatesOfAsset(asset.value())) {
                        assetStates.push_back(assetState.toJson());
                    }
                    result["assetStates"] = assetStates;
                }
                res << result.dump();
            });
        multiplexer.handle("/wallet-statistics/{id:\\d+}")
            .get([this](served::response& res, const served::request& req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                const auto walletId = std::stoi(req.params["id"]);
                const auto wallet = this->myWallets->getWallet(walletId);
                nlohmann::json result;
                if (wallet.has_value()) {
                    result["basicWalletStatistics"] = this->myWallets->getBasicWalletStatistics(wallet.value()).toJson();
                }
                res << result.dump();
            });
        multiplexer.handle("/asset-statistics/{id:\\d+}")
            .get([this](served::response& res, const served::request& req) {
                res.set_header("Access-Control-Allow-Origin", "*");
                res.set_header("Content-Type", "application/json");
                const auto assetId = std::stoi(req.params["id"]);
                const auto asset = this->myWallets->getAsset(assetId);
                nlohmann::json result;
                if (asset.has_value()) {
                    result["basicAssetStatistics"] = this->myWallets->getBasicAssetStatistics(asset.value()).toJson();
                }
                res << result.dump();
            });
    }

    void run() {
        server.run(1);
    }
private:
    std::unique_ptr<frontend::MyWallets> myWallets;
    served::multiplexer multiplexer;
    served::net::server server;
};

} // rest
} // my_wallets
