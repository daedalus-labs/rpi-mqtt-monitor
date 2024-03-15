# Raspberry Pi Monitor

This project is a C++ based driver for making Raspberry Pi information available via MQTT.

The driver has the following dependencies:

| Library                                              | Minimum Version |
| ---------------------------------------------------- | --------------- |
| [`libuv`](https://libuv.org/)                        | 1.43.0          |
| [`libspdlog`](https://github.com/gabime/spdlog/wiki) | 1.9.2           |
| [`json`](https://github.com/nlohmann/json)           | 3.11.2          |

## Build

Both GNU and Clang toolchains have been tested, it is recommended that the `CC` and `CXX` environment variables are used to set the desired compiler. For example, to use the Clang toolchain
run the following before using `cmake`:

```bash
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
```

To install this driver, the it is recommended to use `install.sh`, as it will configure and install the driver as a systemd service:

```bash
./install.bash --service
```

### Developer loop

If you are a developer and wish to make modifications and test, using `cmake` commands as follows will allow you to build and test:

```bash
cmake -S . -B build
cmake --build build
```

### Installation

The driver can be installed with a systemd service (`fanshim-driver`) using the `instal.sh` script or the `--install` flag to cmake:

```bash
cmake --install build
```

The `install.sh` script will enable the service automatically.

## Monitoring via MQTT

The dryer publishes a collection fo MQTT topics for monitoring the status of the Raspberry Pi. All topics are relative
to the device name (i.e. if the device is named `daryl`, the container humidity will be available on `daryl/container/humidity`).

| Topic                | Description                             | Data Type |
| -------------------- | --------------------------------------- | --------- |
| `info/total_swap`    | The total swap available, in kilobytes. | Integer   |
| `info/total_cores`   | The total cores available.              | Integer   |
| `info/total_memory`  | The total RAM available, in kilobytes.  | Integer   |
| --                   | --                                      | --        |
| `status/uptime`      | The uptime of the device, in seconds.   | Integer   |
| `status/free_swap`   | The free swap, in kilobytes.            | Integer   |
| `status/free_memory` | The available RAM, in kilobytes.        | Integer   |
| `status/temperature` | The CPU temperature, in Celsius.        | Float     |
| `status/load`        | The total CPU load, as a percentage.    | Float     |

Finally, there are some MQTT topics that provide metadata on the device status:

| Topic     | Description                 | Data Type |
| --------- | --------------------------- | --------- |
| `version` | The version of this driver. | String    |

It should be noted that the MQTT interface will require all data be encoded as a string; the `Data Type` column above specifies a constraint
on the values the string can take.

## Driver Configuration

 The behavior of the driver can be driven by a configuration file located at `/etc/rpi-monitor.json`. This file is read in at runtime. If any value is invalid, the entire
 configuration will revert to default.

 All fields in the configuration file are optional, except `on-threshold` and `off-threshold` which must be specified as a pair.

 The JSON file supports the following configuration items:

 | Configuration Item | Type   | Description                                      | Valid Values           |
 | ------------------ | ------ | ------------------------------------------------ | ---------------------- |
 | `broker`           | string | The IPv4 address or hostname of the MQTT broker. | Any string is accepted |
 | `name`             | string | The device name for MQTT communication.          | Any string is accepted |

An example of a valid configuration file:

 ```json
 {
    "broker": 65,
    "name": 45
}
 ```

### Default Values

If the configuration file is not present or is invalid, the following values will be used:

 | Configuration Item | Default Value       |
 | ------------------ | ------------------- |
 | `broker`           | "localhost"         |
 | `name`             | The device hostname |
