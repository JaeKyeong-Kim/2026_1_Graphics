# 2026_1 Graphics

Course repository for the 2026 Spring Graphics class.

This project collects weekly OpenGL practice work for macOS. Each week is stored as an independent CMake target so that one exercise can be built and tested without rebuilding the entire course history.

## Overview

| Item | Value |
|---|---|
| Language | C++17 |
| Build system | CMake |
| Graphics API | Legacy OpenGL immediate mode |
| Window/input API | GLUT / FreeGLUT-compatible API |
| Primary platform | macOS |

## Repository Layout

```text
2026_1_Graphics/
├── CMakeLists.txt
├── README.md
├── rebuild_target.sh
├── week01/
├── week02/
├── ...
├── week18_test_01/
├── week18_test_02/
└── build/
```

- `weekNN_01`, `weekNN_02`: regular weekly exercises
- `weekNN_test_01`, `weekNN_test_02`: in-class or submission-oriented variants
- `CMakeLists.txt`: root build entry for all tracked week targets
- `rebuild_target.sh`: helper script to configure, build, and run one target

Each week folder contains its own `main.cpp` and local `CMakeLists.txt`.

## macOS Setup

This repository is intended for macOS users.

### Requirements

- Xcode Command Line Tools
- CMake
- Homebrew

Install CMake with Homebrew if needed:

```bash
brew install cmake
```

OpenGL and GLUT are linked through the macOS frameworks used by the current project layout.

## Build Workflow

### 1. Configure

Run this once after cloning, or again after editing `CMakeLists.txt`.

```bash
cmake -S . -B build
```

### 2. Build One Target

Example:

```bash
cmake --build build --target week18_test_01 -j
```

### 3. Run One Target

Example:

```bash
./build/week18_test_01/week18_test_01
```

## Fast Build + Run

Use the helper script to configure, build, and run a target in one step.

```bash
./rebuild_target.sh week18_test_01
```

You can also pass the executable path shown under `build/`.

```bash
./rebuild_target.sh build/week18_test_01/week18_test_01
```

The program window stays open until you close it.

## Typical Workflow

```text
Edit source -> rebuild target -> run executable -> check output -> repeat
```

In practice:

```bash
./rebuild_target.sh week17_03
```

or:

```bash
cmake --build build --target week17_03 -j
./build/week17_03/week17_03
```

## Important Notes

- Saving `main.cpp` does not update the executable automatically.
- Changes appear only after rebuilding the matching target.
- macOS will show OpenGL and GLUT deprecation warnings during build. That is expected for this class setup.
- The codebase intentionally uses immediate mode APIs because the class focuses on foundational graphics concepts.
- Several week folders remain in the repository even when similar code appears later, because they represent separate lecture checkpoints.

## Course Topics

The weekly exercises generally cover:

- GLUT window setup
- 2D primitives and viewport handling
- Orthographic projection
- Point, line, strip, and fan primitives
- Basic transformations
- Keyboard interaction
- Face culling
- Depth testing

Recent weeks focus more on:

- Winding order and front/back face handling
- Triangle-fan-based circles and cones
- Culling and depth-test interactions
- Outline and wireframe rendering

## License

This repository uses the MIT License included in the repository.
