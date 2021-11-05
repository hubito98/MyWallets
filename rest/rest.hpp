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
                const std::string login = req.params["login"];
                const auto user = this->myWallets->getUser(login);
                nlohmann::json result;
                if (user.has_value()) {
                    std::vector<nlohmann::json> userWallets;
                    for (const auto& wallet : this->myWallets->getUserWallets(user.value())) {
                        userWallets.push_back(wallet.toJson());
                    }
                    result["user"] = user->toJson();
                    result["wallets"] = userWallets;
                }
                res << result.dump();
            });
        multiplexer.handle("/users")
            .get([this](served::response & res, const served::request & req) {
                std::vector<nlohmann::json> users;
                for (const auto& user : this->myWallets->getUsers()) {
                    users.push_back(user.toJson());
                }
                nlohmann::json result;
                result["users"] = users;
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
