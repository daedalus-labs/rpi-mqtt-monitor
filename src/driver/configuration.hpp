/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/
#pragma once

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <map>
#include <string>
#include <string_view>


inline constexpr std::string_view DEFAULT_CONFIGURATION_FILE = "/etc/rpi-monitor.json";


namespace driver {
struct Configuration
{
public:
    Configuration();
    Configuration(const std::filesystem::path& configuration_file);


    /**
     * @note The MQTT Broker can be an IPv4 address or a hostname. This should be passed through a DNS resolver.
     * @return The MQTT Broker.
     */
    const std::string& broker() const;

    /**
     * @return The device name to be used for MQTT communication.
     */
    const std::string& deviceName() const;

private:
    void _load(const std::filesystem::path& configuration_file);

    std::string _broker;
    std::string _name;
};
} // namespace driver
