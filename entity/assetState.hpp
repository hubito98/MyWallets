#pragma once

#include <string>
#include <ctime>

class AssetState {
public:
    AssetState(int id, const std::time_t& date, double value, double income)
    : id(id), date(date), value(value), income(income) {}

    int getId() const {
        return id;
    }

    std::time_t getDate() const {
        return date;
    }

    double getValue() const {
        return value;
    }

    double getIncome() const {
        return income;
    }
private:
    int id;
    std::time_t date;
    double value;
    double income;
};