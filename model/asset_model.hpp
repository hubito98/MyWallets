#pragma once

#include <string>
#include <iostream>

#include "entity/asset.hpp"

namespace my_wallets {

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
private:
    size_t id;
    std::string type;
    std::string description;
};

}