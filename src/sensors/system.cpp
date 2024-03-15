/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/

#include "sensors/system.hpp"

#include <sys/sysinfo.h>

#include <array>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>


inline constexpr float ERROR_LOAD = -1.0;

namespace sensors {
constexpr uint32_t bytesToKilobytes(uint64_t bytes)
{
    constexpr float BYTES_PER_KILOBYTE = 1024;
    return static_cast<uint32_t>(bytes / BYTES_PER_KILOBYTE);
}

constexpr float sysinfoLoadToPercent(uint64_t load)
{
    // The math here is pretty atypical in order for `sysinfo` to avoid the use of floats in the sys_info struct.
    // The loads are stored such that a CPU load of "1.02" is stored as: (int)(1.02 * 2^SI_LOAD_SHIFT).
    // To normalize this, these values need multiplied by 1/2^SI_LOAD_SHIFT.
    constexpr float LOAD_DIVISOR = 1 << SI_LOAD_SHIFT;
    return load / LOAD_DIVISOR;
}

bool get(SystemState& state)
{
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) < 0) {
        fprintf(stderr, "Failed to retrieve system information: %s\n", std::strerror(errno));
        return false;
    }

    state.Uptime = sys_info.uptime;
    state.FreeSwap = bytesToKilobytes(sys_info.freeswap);
    state.Load = sysinfoLoadToPercent(sys_info.loads[0]);
    state.AvailableMemory = bytesToKilobytes(sys_info.freeram);

    uint32_t temp_raw;
    std::array<char, 256> temp_string;
    std::ifstream temp_file("/sys/class/thermal/thermal_zone0/temp", std::ios::in);
    temp_file.getline(temp_string.data(), temp_string.size());
    if (std::sscanf(temp_string.data(), "%u", &temp_raw) == 1) {
        constexpr float THERMAL_DIVISOR = 1000;
        state.Temperature = temp_raw / THERMAL_DIVISOR;
        return true;
    }

    return false;
}

bool get(SystemInfo& info)
{
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) < 0) {
        fprintf(stderr, "Failed to retrieve system information: %s\n", std::strerror(errno));
        return false;
    }

    info.TotalCores = static_cast<uint16_t>(get_nprocs());
    info.TotalSwap = bytesToKilobytes(sys_info.totalswap);
    info.TotalMemory = bytesToKilobytes(sys_info.totalram);
    return true;
}
} // namespace sensors