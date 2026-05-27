#!/bin/zsh

# Usage:
#   ./rebuild_target.sh <target_name>
#   ./rebuild_target.sh <build_executable_path>
#
# Examples:
#   ./rebuild_target.sh week16_01
#   ./rebuild_target.sh build/week16_01/week16_01
#   ./rebuild_target.sh ./build/week16_test_02/week16_test_02
#
# What this script does:
# 1. Runs CMake configure again so CMakeLists.txt changes are reflected.
# 2. Builds only the requested target.
# 3. Runs the built executable immediately.
#
# Notes:
# - Saving main.cpp does not update ./build/... binaries by itself.
#   The source file and the built executable are different files.
#   You must rebuild after saving source changes.
# - If you changed only .cpp code, step 1 is usually not strictly required,
#   but this script always runs it so you do not have to remember the difference.
# - This script starts the program right after building.
#   Close the program window yourself when you are done testing.

set -euo pipefail

if [[ $# -ne 1 ]]; then
    echo "Usage: ./rebuild_target.sh <target_name|build_executable_path>"
    exit 1
fi

input_path="$1"
repo_root="$(cd "$(dirname "$0")" && pwd)"
build_dir="$repo_root/build"

if [[ "$input_path" == */* ]]; then
    target_name="${input_path:t}"
else
    target_name="$input_path"
fi

echo "[1/2] Configuring CMake..."
cmake -S "$repo_root" -B "$build_dir"

echo "[2/2] Building target: $target_name"
cmake --build "$build_dir" --target "$target_name" -j

target_exec="$build_dir/$target_name/$target_name"
if [[ -x "$target_exec" ]]; then
    echo "Build complete."
    echo "Running:"
    echo "  $target_exec"
    exec "$target_exec"
else
    echo "Build finished, but executable was not found at:"
    echo "  $target_exec"
    echo "Check whether the target name matches the executable name."
fi
