#pragma once

#include <string>
#include <iostream>

#include "entity/asset_state.hpp"
#include "date_handling/date.hpp"

namespace my_wallets {
namespace model {

class AssetStateModel {
public:
    AssetStateModel(const AssetState& assetState)
    : id(assetState.getId()), date(assetState.getDate()),
      value(assetState.getValue()), income(assetState.getIncome()) {}

    size_t getId() const {
        return id;
    }

    friend std::ostream& operator<<(std::ostream& os, const AssetStateModel& assetStateModel) {
        os << "AssetState { id: " << assetStateModel.id << ", date: "<<assetStateModel.date.asString()
                <<", value: "<<assetStateModel.value<<", income: "<<assetStateModel.income<<" }";
        return os;
    }
private:
    size_t id;
    Date date;
    double value;
    double income;
};

} // model
} // my_wallets