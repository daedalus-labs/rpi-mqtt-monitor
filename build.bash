#!/bin/bash

set -e
cpu_cores=$(grep -c ^processor /proc/cpuinfo)
job_count=$(expr $cpu_cores - 2)

if [[ $job_count -lt 1 ]]; then
    job_count=1
fi

case "$1" in
    "--analyze")
        cmake -B build -S .
        cmake --build build --parallel $job_count
        run-clang-tidy -p build -quiet -export-fixes build/clang-tidy-fixes.yaml '^((?!build/msg/).)*$'
        ;;
    "--build")
        cmake -B build  -S . "${@:2}"
        cmake --build build --parallel $job_count
        ;;
    "--package-deb")
        pushd build
            cpack -G DEB
        popd
        ;;
    "--package-rpm")
        pushd build
            cpack -G RPM
        popd
        ;;
    "--clean")
        rm -rf build
        ;;
    *)
        echo "Usage: build.bash [OPTION]"
        echo "  --analyze       Analyzes the C/C++ code in the project"
        echo "  --build         Builds the project without testing"
        echo "  --package-deb   Package the previously built project"
        echo "  --package-rpm   Package the previously built project"
        echo "  --clean         Cleans all project files"
        exit 1
        ;;
esac
