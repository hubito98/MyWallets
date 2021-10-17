#pragma once

#include <string>

#include "date_handling/date.hpp"

namespace my_wallets {

class AssetState {
public:
    AssetState(size_t id, size_t assetId, const Date& date, double value, double income)
    : id(id), assetId(assetId), date(date), value(value), income(income) {}

    size_t getId() const {
        return id;
    }

    size_t getAssetId() const {
        return assetId;
    }

    Date getDate() const {
        return date;
    }

    double getValue() const {
        return value;
    }

    double getIncome() const {
        return income;
    }
private:
    size_t id;
    size_t assetId;
    Date date;
    double value;
    double income;
};

} // my_wallets
