/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/
#pragma once

#include <cstdint>


namespace sensors {
struct SystemInfo
{
    uint32_t TotalSwap;
    uint32_t TotalMemory;
    uint16_t TotalCores;
};

struct SystemState
{
    uint64_t Uptime;
    uint64_t FreeSwap;
    uint64_t AvailableMemory;
    float Temperature;
    float Load;
};

bool get(SystemState &state);
bool get(SystemInfo &info);
} // namespace cpu
