# Raspberry Pi Monitor

This project is a C++ based driver for making Raspberry Pi information available via MQTT.

The driver has the following dependencies:

| Library                                                            | Minimum Version |
| ------------------------------------------------------------------ | --------------- |
| [`libuv`](https://libuv.org/)                                      | 1.43.0          |
| [`libspdlog`](https://github.com/gabime/spdlog/wiki)               | 1.9.2           |
| [`json`](https://github.com/nlohmann/json)                         | 3.11.2          |

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

