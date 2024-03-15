/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/

#include "sensors/system.hpp"

#include <cstdio>

int main(int argc, char** argv)
{
    sensors::SystemState state;
    sensors::SystemInfo info;

    if (!get(state) || !get(info)) {
        return -1;
    }
    printf("%f\n", state.Temperature);
    return 0;
}
