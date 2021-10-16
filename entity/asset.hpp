#pragma once

#include <string>

class Asset {
public:
    Asset(size_t id, size_t walletId, const std::string& type, const std::string& description)
    : id(id), walletId(walletId), type(type), description(description) {}

    size_t getId() const {
        return id;
    }

    size_t getWalletId() const {
        return walletId;
    }

    std::string getType() const {
        return type;
    }

    std::string getDescription() const {
        return description;
    }

private:
    size_t id;
    size_t walletId;
    std::string type;
    std::string description;
};