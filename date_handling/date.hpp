#pragma once

#include <cstddef>
#include <string>

namespace my_wallets {

class Date {
public:
    Date(size_t year, size_t month, size_t day)
    : year(year), month(month), day(day) {};

    std::string asString() const {
        return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
    }

    size_t getYear() const {
        return year;
    }

    size_t getMonth() const {
        return month;
    }

    size_t getDay() const {
        return day;
    }

private:
    size_t year, month, day;
};

} // my_wallets
