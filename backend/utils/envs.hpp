#pragma once

#include <string>
#include <cstdlib>

namespace my_wallets {
namespace utils {

struct DatabaseNameEnvVar {
    static constexpr const char* envName = "DB_NAME";
    static constexpr const char* defaultValue = "test_db";
};

struct ExecuteTypeEnvVar {
    static constexpr const char* envName = "EXECUTE_TYPE";
    static constexpr const char* defaultValue = "rest";
};

struct DbHostEnvVar {
    static constexpr const char* envName = "DB_HOST";
    static constexpr const char* defaultValue = "localhost";
};

struct DbPortEnvVar {
    static constexpr const char* envName = "DB_PORT";
    static constexpr const char* defaultValue = "3306";
};

struct DbUserEnvVar {
    static constexpr const char* envName = "DB_USER";
    static constexpr const char* defaultValue = "user";
};

struct DbPasswordEnvVar {
    static constexpr const char* envName = "DB_PASSWORD";
    static constexpr const char* defaultValue = "password";
};

std::string getEnv(const std::string& envName, const std::string& defaultValue="") {
    auto envValue = std::getenv(envName.c_str());
    return envValue == nullptr ? defaultValue : std::string(envValue);
}

} // utils
} // my_wallets
