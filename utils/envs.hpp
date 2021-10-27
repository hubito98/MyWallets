#pragma once

#include <string>
#include <cstdlib>

namespace my_wallets {
namespace utils {

struct DatabaseNameEnvVar {
    static constexpr const char* envName = "DB_NAME";
    static constexpr const char* defaultValue = "test_db";
};


std::string getEnv(const std::string& envName, const std::string& defaultValue="") {
    auto envValue = std::getenv(envName.c_str());
    return envValue == nullptr ? defaultValue : std::string(envValue);
}

} // utils
} // my_wallets
