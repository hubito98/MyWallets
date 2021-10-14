#pragma once

#include <string>
#include "entity/assetType.hpp"

class Asset {
public:
    Asset(int id, const std::string& description, const AssetType& type)
    : id(id), description(description), type(type) {}

    int getId() const {
        return id;
    }

    std::string getDescription() const {
        return description;
    }

    AssetType getType() const {
        return type;
    }

private:
    int id;
    std::string description;
    AssetType type;
};