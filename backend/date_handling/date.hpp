#pragma once

#include <cstddef>
#include <string>
#include <ctime>

#include "nlohmann/json.hpp"

namespace my_wallets {

class Date {
public:
    Date(size_t year, size_t month, size_t day)
    : year(year), month(month), day(day) {};

    std::string asString() const {
        return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
    }

    nlohmann::json toJson() const {
        nlohmann::json dateJson;
        dateJson["year"] = year;
        dateJson["month"] = month;
        dateJson["day"] = day;
        return dateJson;
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

    int operator-(const Date& rhs) const {
        std::tm t0 = {.tm_mday=(int)rhs.getDay(), .tm_mon=(int)rhs.getMonth()-1, .tm_year=(int)rhs.getYear()-1900};
        std::tm t1 = {.tm_mday=(int)this->getDay(), .tm_mon=(int)this->getMonth()-1, .tm_year=(int)this->getYear()-1900};
        return (int)(std::difftime(std::mktime(&t1), std::mktime(&t0)) / (60 * 60 * 24));
    }

private:
    size_t year, month, day;
};

} // my_wallets
