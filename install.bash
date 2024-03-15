#!/bin/bash
set -e
cpu_cores=$(grep -c ^processor /proc/cpuinfo)
job_count=$(expr $cpu_cores - 2)

if [[ $job_count -lt 1 ]]; then
    job_count=1
fi

case "$1" in
    "--deps")
        git clone https://github.com/nlohmann/json.git .json
        pushd .json
            git checkout v3.11.2
            cmake -S . -B build
            cmake --build build
            sudo cmake --install build
        popd

        rm -rf .json
        sudo apt update
        sudo apt install libuv1-dev libspdlog-dev
        ;;
    "--service")
        cmake -S . -B build
        cmake --build build
        sudo cmake --install build

        sudo systemctl enable fanshim-driver.service
        sudo systemctl start fanshim-driver.service
        ;;
    *)
        echo "Usage: build.bash [OPTION]"
        echo "  --deps          Installs the dependencies required by this project"
        echo "  --service       Installs this project as a service"
        exit 1
        ;;
esac