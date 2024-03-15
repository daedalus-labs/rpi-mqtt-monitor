/*------------------------------------------------------------------------------
Copyright (c) 2024 Joe Porembski
SPDX-License-Identifier: BSD-3-Clause
------------------------------------------------------------------------------*/
#pragma once

#include <cstdint>
#include <string>


/**
 * A wrapper class for access to this driver build and installation information.
 */
class DriverInfo
{
public:
    /**
     * @see [Semantic Versioning](https://semver.org/spec/v2.0.0.html).
     * @return The semantic version of this driver.
     */
    static std::string version();

    /**
     * @return The Unix Epoch time this driver was built.
     */
    static uint64_t buildDate();
};
