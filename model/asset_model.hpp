#pragma once

#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "entity/asset.hpp"

namespace my_wallets {
namespace model {

class AssetModel {
public:
    AssetModel(const Asset& asset)
    : id(asset.getId()), type(asset.getType()), description(asset.getDescription()) {}

    size_t getId() const {
        return id;
    }

    friend std::ostream& operator<<(std::ostream& os, const AssetModel& assetModel) {
        os << "Asset { id: " << assetModel.id << ", type: "<<assetModel.type<<", description: "<<assetModel.description<<" }";
        return os;
    }

    nlohmann::json toJson() const {
        nlohmann::json assetJson;
        assetJson["id"] = id;
        assetJson["type"] = type;
        assetJson["description"] = description;
        return assetJson;
    }

private:
    size_t id;
    std::string type;
    std::string description;
};

} // model
} // my_wallets