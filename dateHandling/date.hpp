#pragma once

#include <cstddef>
#include <string>

class Date {
public:
    Date(size_t year, size_t month, size_t day)
    : year(year), month(month), day(day) {};

    std::string asString() const {
        return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
    }
private:
    size_t year, month, day;
};