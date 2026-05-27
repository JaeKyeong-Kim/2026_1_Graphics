# 2026_1_Graphics - Usage Guide

## Environment

| Item | Value |
|---|---|
| Platform | macOS |
| Compiler | AppleClang |
| Build system | CMake |
| Graphics API | Legacy OpenGL |
| Window library | GLUT / FreeGLUT-compatible API |

This repository uses the macOS OpenGL and GLUT frameworks directly. Deprecation warnings during build are expected for this class.

## Project Structure

```text
2026_1_Graphics/
├── CMakeLists.txt
├── README.md
├── how_to_use.md
├── rebuild_target.sh
├── week01/
├── week02/
├── ...
├── week18_test_01/
├── week18_test_02/
└── build/
```

Each `weekXX...` directory is a separate target with its own `main.cpp` and `CMakeLists.txt`.

## First-Time Setup

From the repository root:

```bash
cmake -S . -B build
```

This generates the build system once for all tracked week targets.

## Build One Target

Example:

```bash
cmake --build build --target week18_test_01 -j
```

## Run One Target

Example:

```bash
./build/week18_test_01/week18_test_01
```

## Fast Build + Run

The helper script below reconfigures, rebuilds, and runs one target in a single command.

```bash
./rebuild_target.sh week18_test_01
```

You can also pass the executable path you usually see in `build/`.

```bash
./rebuild_target.sh build/week18_test_01/week18_test_01
```

## Typical Workflow

```text
Edit source -> build target -> run executable -> check result -> repeat
```

In this repository that usually means:

```bash
./rebuild_target.sh week17_03
```

or

```bash
cmake --build build --target week17_03 -j
./build/week17_03/week17_03
```

## Important Note

Saving a `main.cpp` file does not update the executable automatically.  
The code changes only appear after rebuilding the matching target.
