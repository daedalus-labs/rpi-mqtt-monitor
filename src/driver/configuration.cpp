/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/

#include "driver/configuration.hpp"

#include <nlohmann/json.hpp>

#include <cerrno>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>

#include <unistd.h>

using json = nlohmann::json;


inline constexpr std::string_view BROKER_KEY = "broker";
inline constexpr std::string_view NAME_KEY = "name";
inline constexpr std::string_view DEFAULT_BROKER = "localhost";

namespace driver {
Configuration::Configuration() : Configuration(std::filesystem::path(DEFAULT_CONFIGURATION_FILE))
{}

Configuration::Configuration(const std::filesystem::path& configuration_file) : _broker(DEFAULT_BROKER), _name()
{
    _load(configuration_file);
}

const std::string& Configuration::broker() const
{
    return _broker;
}

const std::string& Configuration::deviceName() const
{
    return _name;
}

void Configuration::_load(const std::filesystem::path& configuration_file)
{
    json config;

    std::ifstream config_stream(configuration_file, std::ios::in);
    if (!config_stream) {
        return;
    }

    config = json::parse(config_stream);
    config_stream.close();

    if (config.contains(BROKER_KEY)) {
        _broker = config[BROKER_KEY].get<std::string>();
    }

    char hostname[UINT8_MAX];
    if (config.contains(NAME_KEY)) {
        _name = config[NAME_KEY].get<std::string>();
    }
    else if(gethostname(hostname, UINT8_MAX) != 0) {
        _name = hostname;
    }
    else{
        fprintf(stderr, "Failed to retrieve hostname\n");
    }
}
} // namespace driver
