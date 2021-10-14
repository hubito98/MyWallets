#pragma once

#include <string>

class AssetType {
public:
    AssetType(const std::string& name)
    : name(name) {}

    const std::string& getName() const {
        return name;
    }
private:
    std::string name;
};